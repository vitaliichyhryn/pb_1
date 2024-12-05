#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include "clr_stdin.h"
#include "str.h"

#define INPUT_BUFFER_SIZE 16
#define MENU_BUFFER_SIZE (1 + 2)

int main() {
	double a, b, c, d;
	double q, p, u, v, phi, disc, eps;
	double complex w1, w2, x1, x2, x3;

	// Inform the user about the program
	printf("The program solves cubic equations of the form ax^3 + bx^2 + cx + d = 0, where a is nonzero.\n");

	// User interface of the program in a do while loop
	char *buffer = malloc(INPUT_BUFFER_SIZE);
	bool exit_condition = false;

	do {
		// Get coefficients
		printf("Enter coefficient a: ");
		fgets(buffer, INPUT_BUFFER_SIZE, stdin);

		if (!ends_on_newline(buffer)) {
			printf("The entered string is larger than the input buffer.\n");
			clr_stdin();
			continue;
		} else if (!is_double(buffer)) {
			printf("The entered string is not a floating-point number.\n");
			continue;
		} else {
			a = strtod(buffer, NULL);
		}

		if (a == 0.0) {
			printf("Coefficient a cannot equal to zero.\n");
			continue;
		}

		printf("Enter coefficient b: ");
		fgets(buffer, INPUT_BUFFER_SIZE, stdin);

		if (!ends_on_newline(buffer)) {
			printf("The entered string is larger than the input buffer.\n");
			clr_stdin();
			continue;
		} else if (!is_double(buffer)) {
			printf("The entered string is not a floating-point number.\n");
			continue;
		} else {
			b = strtod(buffer, NULL);
		}

		printf("Enter coefficient c: ");
		fgets(buffer, INPUT_BUFFER_SIZE, stdin);
		if (!ends_on_newline(buffer)) {
			printf("The entered string is larger than the input buffer.\n");
			clr_stdin();
			continue;
		} else if (!is_double(buffer)) {
			printf("The entered string is not a floating-point number.\n");
			continue;
		} else {
			c = strtod(buffer, NULL);
		}

		printf("Enter coefficient d: ");
		fgets(buffer, INPUT_BUFFER_SIZE, stdin);
		if (!ends_on_newline(buffer)) {
			printf("The entered string is larger than the input buffer.\n");
			clr_stdin();
			continue;
		} else if (!is_double(buffer)) {
			printf("The entered string is not a floating-point number.\n");
			continue;
		} else {
			d = strtod(buffer, NULL);
		}

		// ???
		p = (3.0 * a * c - pow(b, 2.0)) / (3.0 * pow(a, 2.0));
		q = (2.0 * pow(b, 3.0) - 9.0 * a * b * c + 27.0 * pow(a, 2.0) * d) / 27.0 * pow(a, 3.0);
		disc = pow(q, 2.0) / 4.0 + pow(p, 3.0) / 27.0;
		w1 = (-1.0 + I * sqrt(3.0)) / 2.0;
		w2 = (-1 - I * sqrt(3.0)) / 2.0;
		if (disc == 0.0) {
			u = cbrt(-q / 2.0 + sqrt(disc));
			v = cbrt(-q / 2.0 - sqrt(disc));
			x1 = -0.5 * (u + v) - b / 3.0 * a;
			x2 = u + v - b / 3.0 * a;
			x3 = x2;
		} else if (disc > 0.0) {
			u = cbrt(-q / 2.0 + sqrt(disc));
			v = cbrt(-q / 2.0 - sqrt(disc));
			x1 = u + v - b / 3.0 * a;
			x2 = w1 * u + w2 * v - b / 3.0 * a;
			x3 = w2 * u + w1 * v - b / 3.0 * a;
		} else if (disc < 0.0) {
			eps = 2.0 * sqrt(-p / 3.0);
			phi = acos((3.0 * q) / (eps * p));
			x1 = eps * cos(phi / 3.0) - b / 3.0 * a;
			x2 = eps * cos((phi + 2.0 * M_PI) / 3.0) - b / 3.0 * a;
			x3 = eps * cos((phi + 4.0 * M_PI) / 3.0) - b / 3.0 * a;
		}

		// Print out the roots of the equation
		printf("The roots of the equation are %lf + %lfi, %lf + %lfi, %lf + %lfi\n",
		       creal(x1), cimag(x1), creal(x2), cimag(x2), creal(x3), cimag(x3));

		// Prompt user with a choice to restart or quit the program
		do {
			printf("Enter r to restart the program or q to quit it: ");
			fgets(buffer, MENU_BUFFER_SIZE, stdin);

			if (!ends_on_newline(buffer)) {
				clr_stdin();
			} else if (strcasecmp(buffer, "q\n") == 0) {
				exit_condition = true;
			}
		} while (strcasecmp(buffer, "q\n") != 0 &&
			 strcasecmp(buffer, "r\n") != 0);

	} while (!exit_condition);

	free(buffer);

	return 0;
}