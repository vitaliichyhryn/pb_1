#include <string.h>



void sbsort(char **str_arr, size_t arr_size) {
    for (int i = 0; i < arr_size; i++) {
        for (int j = 0; j < arr_size - 1; j++) {
            if (strcmp(str_arr[j], str_arr[j + 1]) > 0) {
                char *tmp = str_arr[j];
                str_arr[j] = str_arr[j + 1];
                str_arr[j + 1] = tmp;
            }
        }
    }
}