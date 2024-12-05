#include <stdlib.h>

bool is_leap(uint32_t y) {
	return (y % 100 != 0 && y % 4 == 0) || (y % 100 == 0 && y % 400 == 0);
}

uint32_t gauss_day_of_week(uint32_t d, uint32_t m, uint32_t y) {
	uint32_t reg_offsets[] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
	uint32_t leap_offsets[] = {0, 3, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6};

	return (d +
    (is_leap(y) ? leap_offsets[m - 1] : reg_offsets[m - 1]) +
    5 * ((y - 1) % 4) + 4 * ((y - 1) % 100) + 6 * ((y - 1) % 400)) % 7;
}