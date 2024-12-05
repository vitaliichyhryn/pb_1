#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_parsing.h"
#include "clear_input.h"
#include "triangle_ops.h"
#include "math_ops.h"

#define SIDE_MAX 1e18
#define ACC_MAX 16
#define INPUT_BUFFER_SIZE (18 + 16 + 2)
#define MENU_BUFFER_SIZE (1 + 2)

int main() {
	double a, b, c, perimeter, area, altitude, median, bisector;

	// Inform the user about limitations of the program
	printf("A side can only be a positive floating point number that is	less than %.0e.\n"
	       "The number of digits after the decimal point should be less than %d.\n",
	       SIDE_MAX, ACC_MAX);

	// User interface of the program in a do while loop
	char *buffer = malloc(INPUT_BUFFER_SIZE);
	bool exit_condition = false;

	do {
		// Get sides
		printf("Enter side a: ");
		fgets(buffer, INPUT_BUFFER_SIZE, stdin);

		if (!ends_on_newline(buffer)) {
			printf("The entered string is larger than the input buffer.\n");
			clear_input();
			continue;
		} else if (!is_double(buffer)) {
			printf("The entered string is not a floating-point number.\n");
			continue;
		}

		a = strtod(buffer, NULL);

		if (a <= 0.0) {
			printf("A side of a triangle can only be a positive number.\n");
		} else if (size_of_decimal_part(a) > ACC_MAX) {
			printf("The number of digits after the decimal point of the entered side exceeds the upper limit of accuracy.\n");
			continue;
		}

		printf("Enter side b: ");
		fgets(buffer, INPUT_BUFFER_SIZE, stdin);

		if (!ends_on_newline(buffer)) {
			printf("The entered string is larger than the input buffer.\n");
			clear_input();
			continue;
		} else if (!is_double(buffer)) {
			printf("The entered string is not a floating-point number.\n");
			continue;
		}

		b = strtod(buffer, NULL);

		if (b <= 0.0) {
			printf("A side of a triangle can only be a positive number.\n");
		} else if (size_of_decimal_part(a) > ACC_MAX) {
			printf("The number of digits after the decimal point of the entered side exceeds the upper limit of accuracy.\n");
			continue;
		}

		printf("Enter side c: ");
		fgets(buffer, INPUT_BUFFER_SIZE, stdin);

		if (!ends_on_newline(buffer)) {
			printf("The entered string is larger than the input buffer.\n");
			clear_input();
			continue;
		} else if (!is_double(buffer)) {
			printf("The entered string is not a floating-point number.\n");
			continue;
		}

		c = strtod(buffer, NULL);

		if (c <= 0.0) {
			printf("A side of a triangle can only be a positive number.\n");
		} else if (size_of_decimal_part(a) > ACC_MAX) {
			printf("The number of digits after the decimal point of the entered side exceeds the upper limit of accuracy.\n");
			continue;
		}


		if (!is_triangle(a, b, c)) {
			printf("A triangle with such sides does not exist.\n");
			continue;
		}

		// Print out calculation results
		perimeter = get_perimeter(a, b, c);
		area = get_area(a, b, c);
		printf("The perimeter of the triangle is %.*lf.\n",
		       size_of_decimal_part(perimeter), perimeter);
		printf("The area of the triangle is %.*lf.\n",
		       size_of_decimal_part(area), area);

		altitude = get_altitude(a, b, c);
		median = get_median(a, b, c);
		bisector = get_bisector(a, b, c);
		printf("The altitude opposite side a is %.*lf, median is %.*lf, bisector is %.*lf.\n",
		       size_of_decimal_part(altitude), altitude,
		       size_of_decimal_part(median), median,
		       size_of_decimal_part(bisector), bisector);

		altitude = get_altitude(b, a, c);
		median = get_median(b, a, c);
		bisector = get_bisector(b, a, c);
		printf("The altitude opposite side b is %.*lf, median is %.*lf, bisector is %.*lf.\n",
		       size_of_decimal_part(altitude), altitude,
		       size_of_decimal_part(median), median,
		       size_of_decimal_part(bisector), bisector);

		altitude = get_altitude(c, a, b);
		median = get_median(c, a, b);
		bisector = get_bisector(c, a, b);
		printf("The altitude opposite side c is %.*lf, median is %.*lf, bisector is %.*lf.\n",
		       size_of_decimal_part(altitude), altitude,
		       size_of_decimal_part(median), median,
		       size_of_decimal_part(bisector), bisector);

		// Prompt user with a choice to restart or quit the program
		do {
			printf("Enter r to restart the program or q to quit it: ");
			fgets(buffer, MENU_BUFFER_SIZE, stdin);

			if (!ends_on_newline(buffer)) {
				clear_input();
			} else if (strcasecmp(buffer, "q\n") == 0) {
				exit_condition = true;
			}
		} while (strcasecmp(buffer, "q\n") != 0 &&
			 strcasecmp(buffer, "r\n") != 0);

	} while (!exit_condition);

	free(buffer);

	return 0;
}
