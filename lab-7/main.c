
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "err.h"
#include "get.h"
#include "math_ops.h"

#include "funcs.h"

const uint32_t acc_min = 1;
const uint32_t acc_max = 9;
const uint32_t f_num_min = 1;
const uint32_t f_num_max = 2;

const size_t num_max_len = 16;

int main() {
    const size_t acc_max_len = int_char_count((int32_t)acc_max);
    const size_t f_num_max_len = int_char_count((int32_t)f_num_max);

    double n, a, b, x, x0;
    uint32_t f_num, acc;
    double (*f)(double, double);
    double (*dom_f)(double);

    enum method method;

    printf("Accuracy: digits after decimal point (unsigned integer), [%u, %u]\n", acc_min, acc_max);

    do {
        // get func and func ptr
        do {
            clr_err();
            f_num = get_uint(f_num_max_len, "\n1. f(x) = cos(n / x) - 2 * sin(1 / x) + 1 / x"
                                            "\n2. f(x) = sin(ln(x)) - cos(ln(x)) + n * ln(x)"
                                            "\nChoose function: ");
            if (err_code == SUCCESS)
                uint_closed_range(f_num, f_num_min, f_num_max);
            p_err("Error: ", QUIET);
        } while (err_code != SUCCESS);

        switch (f_num) {
            case 1:
                f = f1;
                dom_f = dom_f1;
                break;
            case 2:
                f = f2;
                dom_f = dom_f2;
                break;
            default:
                break;
        }

        // get parameter n
        do {
            clr_err();
            n = get_double(num_max_len, "\nEnter parameter n: ");
            p_err("Error: ", QUIET);
        } while (err_code != SUCCESS);

        // get acc
        do {
            clr_err();
            acc = get_uint(acc_max_len, "\nEnter accuracy: ");
            if (err_code == SUCCESS)
                uint_closed_range(acc, acc_min, acc_max);
            p_err("Error: ", QUIET);
        } while (err_code != SUCCESS);

        // get root find method
        do {
            clr_err();
            method = get_root_find_method();
            p_err("Error: ", QUIET);
        } while (err_code != SUCCESS);

        switch (method) {
            case BISEC: {
                // get interval [a, b]
                printf("\nEnter interval [a, b]:\n");
                do {
                    clr_err();
                    a = get_double(num_max_len, "a: ");
                    if (err_code == SUCCESS) {
                        dom_f(a);
                    }
                    p_err("Error: ", QUIET);
                } while (err_code != SUCCESS);

                do {
                    clr_err();
                    b = get_double(num_max_len, "b: ");
                    if (err_code == SUCCESS)
                        dom_f(b);
                    if (err_code == SUCCESS)
                        double_open_range(b, a, INFINITY);
                    p_err("Error: ", QUIET);
                } while (err_code != SUCCESS);

                x = bisec_method(f, n, a, b, acc);
                p_err("Error: ", QUIET);
                break;
            }
            case NEWTON: {
                // get initial guess x0
                do {
                    clr_err();
                    x0 = get_double(num_max_len, "\nEnter initial guess x0: ");
                    if (err_code == SUCCESS)
                        dom_f(x0);
                    p_err("Error: ", QUIET);
                } while (err_code != SUCCESS);

                x = newton_method(f, x0, n, acc);
                p_err("Error: ", QUIET);
                break;
            }
            case NO_METHOD:
                break;
        }

        if (err_code == SUCCESS)
            printf("\nx: %.*lf\n", acc, x);
    } while(!get_exit());

    return EXIT_SUCCESS;
}
