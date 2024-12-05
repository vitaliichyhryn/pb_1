#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clr_stdin.h"
#include "err.h"
#include "str.h"

enum mode {
    NO_MODE,
    MANUAL,
    RANDOM
};

enum method {
    NO_METHOD,
    BISEC,
    NEWTON
};

const size_t buf_padding = 2;
const size_t key_len = 1;

int64_t get_int(size_t num_len, char *get_msg) {
    size_t buf_size = num_len + buf_padding;
    char *buf = (char *)calloc(buf_size, sizeof(char));

    printf("%s", get_msg);
    fgets(buf, (int)buf_size, stdin);

    if (!ends_on_newline(buf)) {
        free(buf);
        err_code = STR_OVERFLOW;
        clr_stdin();
        return 0;
    } else if (!is_int(buf)) {
        free(buf);
        err_code = NOT_INT;
        return 0;
    } else {
        int64_t val = strtol(buf, NULL, 10);
        free(buf);
        return val;
    }
}

uint64_t get_uint(size_t num_len, char *get_msg) {
    size_t buf_size = num_len + buf_padding;
    char *buf = (char *)calloc(buf_size, sizeof(char));

    printf("%s", get_msg);
    fgets(buf, (int)buf_size, stdin);

    if (!ends_on_newline(buf)) {
        free(buf);
        err_code = STR_OVERFLOW;
        clr_stdin();
        return 0;
    } else if (!is_uint(buf)) {
        free(buf);
        err_code = NOT_UINT;
        return 0;
    } else {
        uint64_t val = strtoul(buf, NULL, 10);
        free(buf);
        return val;
    }
}

double get_double(size_t num_len, char *get_msg) {
    size_t buf_size = num_len + buf_padding;
    char *buffer = (char *)calloc(buf_size, sizeof(char));

    printf("%s", get_msg);
    fgets(buffer, (int)buf_size, stdin);

    if (!ends_on_newline(buffer)) {
        free(buffer);
        err_code = STR_OVERFLOW;
        clr_stdin();
        return 0;
    } else if (!is_double(buffer)) {
        free(buffer);
        err_code = NOT_FLOAT;
        return 0;
    } else {
        double val = strtod(buffer, NULL);
        free(buffer);
        return val;
    }
}

char *get_str(size_t str_len, char *get_msg) {
    size_t buf_size = str_len + buf_padding;
    char *str = (char *)calloc(buf_size, sizeof(char));

    printf("%s", get_msg);
    fgets(str, (int32_t)(buf_size), stdin);

    if (!ends_on_newline(str)) {
        clr_stdin();
        err_code = STR_OVERFLOW;
        return str;
    } else {
        str[strlen(str) - 1] = '\0';
        return str;
    }
}

enum mode get_mode() {
    char *mode_str = get_str(key_len, "\nEnter m to manually enter values or r to randomly generate them: ");

    if (strcasecmp(mode_str, "m") == 0) {
        free(mode_str);
        return MANUAL;
    } else if (strcasecmp(mode_str, "r") == 0) {
        free(mode_str);
        return RANDOM;
    } else {
        free(mode_str);
        err_code = NOT_AN_OPTION;
        return NO_MODE;
    }
}

enum method get_root_find_method() {
    char *mode_str = get_str(key_len, "\nEnter b to use bisection method or n to use Newton's method: ");

    if (strcasecmp(mode_str, "b") == 0) {
        free(mode_str);
        return BISEC;
    } else if (strcasecmp(mode_str, "n") == 0) {
        free(mode_str);
        return NEWTON;
    } else {
        free(mode_str);
        err_code = NOT_AN_OPTION;
        return NO_METHOD;
    }
}

bool get_exit() {
    char *exit_str = get_str(key_len, "\nEnter any key to restart the app or q to quit it: ");
    system("clear");

    if (strcasecmp(exit_str, "q") == 0) {
        free(exit_str);
        return true;
    } else {
        free(exit_str);
        return false;
    }
}

void free_p_arr(void **arr, size_t arr_size) {
    for (size_t i = 0; i < arr_size; ++i) {
        free(arr[i]);
    }
    free(arr);
}