#include <stdio.h>
#include <stdlib.h>

#include "err.h"
#include "get.h"
#include "math_ops.h"
#include "rand.h"
#include "sort.h"

const uint8_t str_num_min = 1, str_num_max = 25;
const uint8_t str_len_min = 1, str_len_max = 80;

int main() {
    const size_t str_num_max_len = int_char_count(str_num_max);

    enum mode mode;

    uint8_t str_num;
    char **str_arr;

    printf("String number: unsigned integer, [%u; %u]\n"
           "String length: unsigned integer, [%u; %u]\n",
           str_num_min, str_num_max, str_len_min, str_len_max);

    do {
        // Get mode
        do {
            err_code = SUCCESS;
            mode = get_mode();
            p_err("Error");
        } while (err_code != SUCCESS);

        switch (mode) {
            case MANUAL: {
                // Get string number
                do {
                    err_code = SUCCESS;
                    str_num = get_uint(str_num_max_len, "\nEnter the number of strings: ");
                    if (err_code == SUCCESS) uint_closed_range(str_num, str_num_min, str_num_max);
                    p_err("Error");
                } while (err_code != SUCCESS);

                // Get strings
                str_arr = (char**)calloc(str_num, sizeof(char*));
                printf("\nEnter strings:\n");
                for (int i = 0; i < str_num; i++) {
                    do {
                        err_code = SUCCESS;
                        str_arr[i] = get_str(str_len_max, "");
                        p_err("Error");
                    } while (err_code != SUCCESS);
                }

                break;
            }
            case RANDOM: {
                str_num = arc4random_uniform(str_num_max - str_num_min) + str_num_min;

                // Generate random string array
                str_arr = (char**)calloc(str_num, sizeof(char*));
                for (int i = 0; i < str_num; i++) {
                    str_arr[i] = rand_alphanumeric_str(arc4random_uniform(str_len_max - str_len_min) + str_len_min);
                }

                printf("\nString number: %d\n"
                       "\nArray of random strings:\n", str_num);
                for (int i = 0; i < str_num; i++) {
                    printf("%s\n", str_arr[i]);
                }

                break;
            }
            default:
                continue;
        }

        sbsort(str_arr, str_num);

        printf("\nSorted array of strings:\n");
        for (int i = 0; i < str_num; i++) {
            printf("%s\n", str_arr[i]);
        }

        // Free memory allocated for elements of the array, then for the array itself
        for (int i = 0; i < str_num; i++) {
            free(str_arr[i]);
        }
        free(str_arr);
    } while (!get_exit());

    return EXIT_SUCCESS;
}