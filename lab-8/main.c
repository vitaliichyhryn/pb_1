#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "complex_ops.h"
#include "err.h"
#include "get.h"
#include "math_ops.h"

const uint32_t crct_min = 1;
const uint32_t crct_max = 4;
const uint32_t acc_min = 1;
const uint32_t acc_max = 16;
const double var_min = 0;
const double var_max = 1e9;

const uint32_t pad_size = 25;

int main() {
    const size_t crct_max_len = int_char_count((int32_t)crct_max);
    const size_t acc_max_len = int_char_count((int32_t)acc_max);
    const size_t var_max_len = int_char_count((int32_t)var_max);

    uint32_t crct, acc;
    double r1, r2, l, c, f, f0, f_low, f_high, f_step, w;
    comp z_num, z_den;

    printf("f lower bound: floating point, (%.0e, %.0e)\n"
           "f higher bound: floating point, (f lower bound, %.0e)\n"
           "f step: floating point, (f lower bound, f higher bound)\n"
           "R, L, C: floating point, (%.0e, %.0e)\n"
           "Accuracy: digits after decimal point (unsigned integer), [%u, %u]\n",
           var_min, var_max, var_max, var_min, var_max, acc_min, acc_max);
    do {
        // get circuit
        do {
            clr_err();
            crct = get_uint(crct_max_len, "\nChoose electrical circuit (from 1 to 4): ");
            if (err_code == SUCCESS)
                uint_closed_range(crct, crct_min, crct_max);
            p_err("Error: ", QUIET);
        } while (err_code != SUCCESS);

        // get frequency min
        do {
            clr_err();
            f_low = get_double(var_max_len, "\nEnter lower bound of frequency f: ");
            if (err_code == SUCCESS)
                double_open_range(f_low, var_min, var_max);
            p_err("Error: ", QUIET);
        } while (err_code != SUCCESS);

        // get frequency max
        do {
            clr_err();
            f_high = get_double(var_max_len, "Enter higher bound of frequency f: ");
            if (err_code == SUCCESS)
                double_open_range(f_high, f_low, var_max);
            p_err("Error: ", QUIET);
        } while (err_code != SUCCESS);

        // get frequency step
        do {
            clr_err();
            f_step = get_double(var_max_len, "Enter step of frequency f: ");
            if (err_code == SUCCESS)
                double_open_range(f_step, var_min, f_high);
            p_err("Error: ", QUIET);
        } while (err_code != SUCCESS);

        // get first resistance
        do {
            clr_err();
            r1 = get_double(var_max_len, "\nEnter resistance R1: ");
            if (err_code == SUCCESS)
                double_open_range(r1, var_min, var_max);
            p_err("Error: ", QUIET);
        } while (err_code != SUCCESS);

        if (uint_closed_range(crct, 3, 4)) {

        }

        switch (crct) {
            case 3: case 4: {
                // get second resistance
                do {
                    clr_err();
                    r2 = get_double(var_max_len, "Enter resistance R2: ");
                    if (err_code == SUCCESS)
                        double_open_range(r2, var_min, var_max);
                    p_err("Error: ", QUIET);
                } while (err_code != SUCCESS);
                break;
            }
            default:
                break;
        }


        // get inductance
        do {
            clr_err();
            l = get_double(var_max_len, "\nEnter inductance L: ");
            if (err_code == SUCCESS)
                double_open_range(l, var_min, var_max);
        } while (err_code != SUCCESS);

        // get capacitance
        do {
            clr_err();
            c = get_double(var_max_len, "\nEnter capacitance C: ");
            if (err_code == SUCCESS)
                double_open_range(c, var_min, var_max);
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

        // get table
        f = f_low;
        size_t arr_size = (size_t)((f_high - f_low) / f_step) + 1;
        comp z_arr[arr_size];
        for (size_t i = 0; i < arr_size; ++i) {
            w = 2 * M_PI * f;
            switch (crct) {
                case 1: {
                    z_num.rl = l / c;
                    z_den.rl = r1;
                    z_num.im = - r1 / (w * c);
                    z_den.im = w * l - 1 / (w * c);
                    break;
                }
                case 2: {
                    z_num.rl = l / c;
                    z_den.rl = r1;
                    z_num.im = r1 / (w * c);
                    z_den.im = w * l - 1 / (w * c);
                    break;
                }
                case 3: {
                    z_num.rl = r1 * r2;
                    z_den.rl = r1 + r2;
                    z_num.im = r1 * (w * l - 1 / (w * c));
                    z_den.im = w * l - 1 / (w * c);
                    break;
                }
                case 4: {
                    z_num.rl = r1 * r2 + l / c;
                    z_den.rl = r1 + r2;
                    z_num.im = w * l * r1 - r2 / (w * c);
                    z_den.im = w * l - 1 / (w * c);
                    break;
                }
                default:
                    break;
            }
            z_arr[i] = fract_comp(z_num, z_den);
            f += f_step;
        }

        f0 = 1.0 / (2.0 * M_PI * sqrt(l * c));

        // print out table
        printf("\n%-*s | %s\n", pad_size, "f", "z");

        f = f_low;
        for (size_t i = 0; i < arr_size; i++) {
            printf("%-*.*e | ", pad_size, acc, f);
            pcomp("", z_arr[i], acc);
            f += f_step;
        }

        printf("\nf0: %.*e\n", acc, f0);
    } while (!get_exit());

    return EXIT_SUCCESS;
}