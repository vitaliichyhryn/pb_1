#include <stdio.h>
#include <stdlib.h>

#include "err.h"
#include "get.h"
#include "math_ops.h"

const uint32_t x_num_min = 1;
const uint32_t x_num_max = 16;
const uint32_t acc_min = 1;
const uint32_t acc_max = 16;

const size_t num_max_len = 16;

int main() {
    const size_t x_num_max_len = int_digit_count((int32_t)x_num_max);
    const size_t acc_max_len = int_digit_count((int32_t)acc_max);

    uint32_t x_num, acc;
    double **a, *b, *x;

    printf("Variable number: unsigned integer, [%u, %u]\n"
           "Accuracy: digits after decimal point (unsigned integer), [%u, %u]\n",
           x_num_min, x_num_max, acc_min, acc_max);

    do {
        // get variable number
        do {
            clr_err();
            x_num = get_uint(x_num_max_len, "\nEnter variable number: ");
            if (err_code == SUCCESS)
                uint_closed_range(x_num, x_num_min, x_num_max);
            p_err("Error: ", QUIET);
        } while (err_code != SUCCESS);

        // allocate memory for linear system
        a = (double **)calloc(x_num, sizeof(double*));
        for (size_t i = 0; i < x_num; ++i) {
            a[i] = (double *)calloc(x_num, sizeof(double));
        }
        b = (double *)calloc(x_num, sizeof(double));

        // get coefs and free terms
        for (size_t i = 0; i < x_num; ++i) {
            printf("\nEnter coefficients a:\n");
            for (size_t j = 0; j < x_num; ++j) {
                printf("a%lu%lu: ", i + 1, j + 1);
                do {
                    clr_err();
                    a[i][j] = get_double(num_max_len, "");
                    p_err("Error: ", QUIET);
                } while (err_code != SUCCESS);
            }
            printf("\nEnter free term b:\nb%lu: ", i + 1);
            do {
                clr_err();
                b[i] = get_double(num_max_len, "");
                p_err("Error: ", QUIET);
            } while (err_code != SUCCESS);
        }

        if (jacobi_converges(a, x_num)) {
            // get calc acc
            do {
                clr_err();
                acc = get_uint(acc_max_len, "\nEnter accuracy: ");
                if (err_code == SUCCESS)
                    uint_closed_range(acc, acc_min, acc_max);
                p_err("Error: ", QUIET);
            } while (err_code != SUCCESS);

            x = jacobi_method(a, b, x_num, acc);

            putchar('\n');
            for (size_t i = 0; i < x_num; ++i) {
                printf("x%lu: %.*lf\n", i + 1, acc, x[i]);
            }

            free(x);
        } else {
            p_err("Error: ", QUIET);
        }

        free_p_arr((void **)a, x_num);
        free(b);
    } while (!get_exit());

    return EXIT_SUCCESS;
}