#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clear_input.h"
#include "math_ops.h"
#include "string_parsing.h"

#define RADICAND_MIN (-1e+18)
#define RADICAND_MAX 1e18
#define INDEX_MIN (-1000000)
#define INDEX_MAX 1000000
#define ACCURACY_MAX 16
#define INPUT_BUFFER_SIZE (18 + 16 + 2)
#define MENU_BUFFER_SIZE 3

int main() {
	double radicand;
	int index, accuracy;

	// Inform the user about limitations of the program
	printf("The radicand can be any real number that is greater than %.0e and less than %.0e.\n"
	       "The number of digits after the decimal point should be less than the upper limit of accuracy.\n",
	       RADICAND_MIN, RADICAND_MAX);
	printf("The index can be any non-zero integer that is greater than %d and less than %d.\n"
	       "The accuracy can be any number of digits after the decimal point that is less than %d.\n",
	       INDEX_MIN, INDEX_MAX);
	printf("The accuracy can be any number of digits after the decimal point that is less than %d.\n",
	       ACCURACY_MAX);

	// User interface of the program in a do while loop
	char *buffer = malloc(INPUT_BUFFER_SIZE);
	bool exit_condition = false;

	do {
		// Get radicand
		printf("Enter the radicand: ");
		fgets(buffer, INPUT_BUFFER_SIZE, stdin);

		if (!ends_on_newline(buffer)) {
			printf("The entered string is larger than the input buffer.\n");
			clear_input();
			continue;
		} else if (!is_double(buffer)) {
			printf("The entered string is not a floating-point number.\n");
			continue;
		} else if (size_of_string_decimal_part(buffer) >= ACCURACY_MAX) {
			printf("The number of digits after the decimal point of the entered radicand exceeds the "
			       "upper limit of accuracy.\n");
			continue;
		} else {
			radicand = strtod(buffer, NULL);
		}

		if (!(radicand > RADICAND_MIN && radicand < RADICAND_MAX)) {
			printf("The entered radicand is out of operational range.\n");
			continue;
		} else if (size_of_decimal_part(radicand) >= ACCURACY_MAX) {
			printf("The number of digits after the decimal point of the entered radicand exceeds the "
			       "upper limit of accuracy.\n");
			continue;
		}

		// Get index
		printf("Enter the index: ");
		fgets(buffer, INPUT_BUFFER_SIZE, stdin);

		if (!ends_on_newline(buffer)) {
			printf("The entered string is larger than the input buffer.\n");
			clear_input();
			continue;
		} else if (!is_int(buffer)) {
			printf("The entered string is not an integer number.\n");
			continue;
		} else {
			index = (int) strtol(buffer, NULL, 10);
		}

		if (index == 0) {
			printf("A root with an index of zero is not defined.\n");
			continue;
		} else if (radicand == 0.0 && index < 0) {
			printf("A root with a radicand of zero and a negative index is not defined.\n");
			continue;
		} else if (radicand < 0.0 && is_even(index)) {
			printf("A root with a negative radicand and an even index is not defined on the plane of real"
			       " numbers.\n");
			continue;
		} else if (!(index > INDEX_MIN && index < INDEX_MAX)) {
			printf("The entered index is out of operational range.\n");
			continue;
		}

		// Get accuracy
		printf("Enter the accuracy: ");
		fgets(buffer, INPUT_BUFFER_SIZE, stdin);

		if (!ends_on_newline(buffer)) {
			printf("The entered string is larger than the input buffer.\n");
			clear_input();
			continue;
		} else if (!is_int(buffer)) {
			printf("The entered string is not an integer number.\n");
			continue;
		} else {
			accuracy = (int) strtol(buffer, NULL, 10);
		}

		if (accuracy <= 0) {
			printf("Accuracy cannot be a non-positive number.\n");
			continue;
		} else if (accuracy >= ACCURACY_MAX) {
			printf("The entered accuracy is out of operational range.\n");
			continue;
		}

		// Print out calculation results
		if (radicand == 0.0) {
			printf("The root with an index of %d and radicand of 0 is 0.\n", index);
		} else if (index == 2) {
			printf("Square root of %.*lf is approximately %.*lf.\n",
			       size_of_decimal_part(radicand), radicand, accuracy, root(radicand, index, accuracy));
		} else if (index == 3) {
			printf("Cube root of %.*lf is approximately %.*lf.\n",
			       size_of_decimal_part(radicand), radicand, accuracy, root(radicand, index, accuracy));
		} else {
			printf("The root with an index of %d and radicand of %.*lf is approximately %.*lf.\n",
			       index, size_of_decimal_part(radicand), radicand, accuracy, root(radicand, index,
											       accuracy));
		}

		// Prompt user with a choice to restart or quit the program
		do {
			printf("Enter r to restart the program or q to quit it: ");
			fgets(buffer, MENU_BUFFER_SIZE, stdin);

			if (!ends_on_newline(buffer)) {
				clear_input();
			} else if (strcasecmp(buffer, "q\n") == 0) {
				exit_condition = true;
			}
		} while (strcasecmp(buffer, "q\n") != 0 && strcasecmp(buffer, "r\n") != 0);

	} while (!exit_condition);

	free(buffer);

	return 0;
}