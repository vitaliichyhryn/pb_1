#include <string.h>
#include <stdlib.h>

const size_t roman_num_size = 15 + 1;

typedef struct {
	int32_t val;
	const char *nmrl;
} roman_nmrl;

char *int_to_roman(int32_t arabic_num) {
	roman_nmrl roman_nmrls[] = {{1,   "I"},
                                {4,   "IV"},
                                {5,   "V"},
                                {9,   "IX"},
                                {10,  "X"},
                                {40,  "XL"},
                                {50,  "L"},
                                {90,  "XC"},
                                {100, "C"},
                                {400, "CD"},
                                {500, "D"},
                                {900,  "CM"},
                                {1000, "M"}};

	char *roman_num = calloc(roman_num_size, sizeof(char));

	for (int32_t i = sizeof(roman_nmrls) / sizeof(roman_nmrl) - 1;
	     arabic_num != 0;) {
		if (arabic_num >= roman_nmrls[i].val) {
			strcat(roman_num, roman_nmrls[i].nmrl);
			arabic_num -= roman_nmrls[i].val;
		} else {
			i--;
		}
	}

	return roman_num;
}