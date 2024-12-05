#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "roman.h"
#include "string_parsing.h"
#include "clear_input.h"

#define ROMAN_NUM_MIN 0
#define ROMAN_NUM_MAX 4000
#define INPUT_BUFFER_SIZE (4 + 2)
#define MENU_BUFFER_SIZE (1 + 2)

int main() {
	int arabic_num;

	// Inform the user about limitations of the program
	printf("A roman number can only be expressed as an integer greater "
	       "than %d and less than %d.\n",
	       ROMAN_NUM_MIN,
	       ROMAN_NUM_MAX);

	// User interface of the program in a do while loop
	char *buffer = malloc(INPUT_BUFFER_SIZE);
	bool exit_condition = false;

	do {
		// Get arabic integer
		printf("Enter an arabic integer: ");
		fgets(buffer, INPUT_BUFFER_SIZE, stdin);

		if (!ends_on_newline(buffer)) {
			printf("The entered string is larger than the input "
			       "buffer.\n");
			clear_input();
			continue;
		} else if (!is_int(buffer)) {
			printf("The entered string is not an integer.\n");
			continue;
		} else {
			arabic_num = (int) strtol(buffer, NULL, 10);
		}

		if (!(arabic_num > ROMAN_NUM_MIN &&
		      arabic_num < ROMAN_NUM_MAX)) {
			printf("The entered integer cannot be expressed as a "
			       "roman number.\n");
			continue;
		}

		// Print out the conversion result
		char *roman_num = int_to_roman(arabic_num);
		printf("%d in roman numerals is %s.\n", arabic_num, roman_num);
		free(roman_num);

		// Prompt user with a choice to restart or quit the program
		do {
			printf("Enter r to restart the program or q to quit "
			       "it: ");
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