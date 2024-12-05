#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *trim(char *str) {
        while (isspace((char)*str)) str++;
        if (*str == 0) return str;
        char *end = str + strlen(str) - 1;
        while (end > str && isspace((char)*end)) end--;
        end[1] = '\0';
        return str;
}

bool ends_on_newline(char *str) {
	return str[strlen(str) - 1] == '\n' || strcmp(str, "\n") == 0;
}

bool is_whitespace(char *str) {
	return strspn(str, " \t\n\v\r") == strlen(str);
}

bool has_sign(char *str) {
    return strcspn(str, "-+") != strlen(str);
}

bool is_int(char *str) {
	char *end_ptr;
	strtol(str, &end_ptr, 10);
	return end_ptr != str && is_whitespace(end_ptr);
}

bool is_uint(char *str) {
    char *end_ptr;
    strtoul(str, &end_ptr, 10);
    return !has_sign(str) && end_ptr != str && is_whitespace(end_ptr);
}

bool is_double(char *str) {
    char *end_ptr;
    strtod(str, &end_ptr);
    return end_ptr != str && is_whitespace(end_ptr);
}

size_t str_fract_len(char *str) {
    if (strcspn(str, ".") == 0) {
        return strcspn(str, "\n") - 1;
    } else {
        return strcspn(str, "\n") - 1 - strcspn(str, ".");
    }
}

int32_t p_str_cmp(char *str1, char *str2) {
    char chr1 = (char)*str1;
    char chr2 = (char)*str2;

    for(int i = 0; chr1 == chr2; i++) {
        chr1 = *(str1 + i);
        chr2 = *(str2 + i);
        if (chr1 == '\0') {
            return (int32_t)chr1 - chr2;
        }
    }

    return (int32_t)(chr1 - chr2);
}