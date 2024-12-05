#include <stdio.h>

int32_t p_char_cmp(const void *char1, const void *char2) {
    return *(char*)char1 - *(char*)char2;
}