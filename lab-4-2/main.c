#include <stdio.h>
#include <stdlib.h>

#include "err.h"
#include "get.h"
#include "math_ops.h"
#include "rand.h"
#include "sort.h"


const size_t arr_size_min = 1;
const size_t arr_size_max = 8192;
const size_t num_fract_len = 3;
const double num_low = -1e3;
const double num_high = 1e3;

int main() {
    const size_t arr_size_max_len = int_char_count((int32_t)arr_size_max);
    size_t arr_size;

    printf("Array size: unsigned integer, [%lu, %lu]\n", arr_size_min, arr_size_max);

    do {
        // Get array size
        do {
            err_code = SUCCESS;
            arr_size = get_uint(arr_size_max_len, "Enter array size: ");
            if (err_code == SUCCESS) uint_closed_range(arr_size, arr_size_min, arr_size_max);
            p_err("Error");
        } while (err_code != SUCCESS);

        // Generate random double array
        double arr[arr_size];
        for (int i = 0; i < arr_size; i++) {
            arr[i] = frand(num_low, num_high);
        }

        printf("Array of random floating point numbers:\n");
        for (int i = 0; i < arr_size; i++) {
            printf("%.*lf\n", (uint32_t)num_fract_len, arr[i]);
        }

        bsort(arr, arr_size);

        printf("Sorted array:\n");
        for (int i = 0; i < arr_size; i++) {
            printf("%.*lf\n", (uint32_t)num_fract_len, arr[i]);
        }
    } while (!get_exit());

    return EXIT_SUCCESS;
}