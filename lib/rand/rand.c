#include <stdlib.h>

double frand(double min, double max) {
    double rand_val = ((double)arc4random()) / UINT32_MAX;
    rand_val = (max - min) * rand_val + min;

    return rand_val;
}

char rand_alphanumeric() {
    char char_index;
    char rand_offset = (char)arc4random_uniform('9' - '0' + 'Z' - 'A' + 1 + 'z' - 'a' + 1);

    if (rand_offset <= '9' - '0') {
        char_index = '0';
    } else if (rand_offset <= '9' - '0' + 'Z' - 'A') {
        char_index = 'A' - ('9' - '0') - 1;
    } else {
        char_index = 'a' - ('9' - '0' + 'Z' - 'A') - 1;
    }

    return (char)(char_index + rand_offset);
}

char *rand_alphanumeric_str(size_t str_len) {
    char *str = (char*)calloc(str_len + 1, sizeof(char));

    for (int i = 0; i < str_len; i++) {
        str[i] = rand_alphanumeric();
    }

    return str;
}