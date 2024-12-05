#include <stdio.h>

void clr_stdin() {
	for (char chr; (chr = getchar()) != '\n';);
}