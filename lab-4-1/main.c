#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "err.h"
#include "get.h"
#include "math_ops.h"
#include "trig_ops.h"

const double x_min = -1e9;
const double x_max = 1e9;
const int32_t step_min = 0;
const size_t acc_min = 1;
const size_t acc_max = 16;
const size_t str_func_len = 3;
const uint32_t padding_size = 25;

int main() {
    const size_t x_max_len =
            int_char_count((int32_t)x_max) > int_char_count((int32_t)x_min) ?
            int_char_count((int32_t)x_max) : int_char_count((int32_t)x_min);
    const size_t acc_max_len = int_char_count((int32_t)acc_max);

    uint32_t term_acc, output_acc;
    double x, x_low, x_high, step;
    char *str_func;
    enum trig_func func;
    size_t arr_size;

    printf("Lower bound of x: degrees (floating point number), [%.0e, %.0e]\n"
           "Higher bound of x: degrees (floating point number), [lower bound of x, %.0e]\n"
           "Step: degrees (floating point number), (%i, higher bound of x)\n"
           "Accuracy of x and output: fractional part length (unsigned integer), [%li, %li]\n"
           "Accuracy of last term of series: fractional part length (unsigned integer), [%li, %li]\n",
           x_min, x_max, x_max, step_min, acc_min, acc_max, acc_min, acc_max);

    do {
        // Get lower bound of x
        do {
            err_code = SUCCESS;
            x_low = get_double(x_max_len, "Enter lower bound of x: ");
            if (err_code == SUCCESS) double_closed_range(x_low, x_min, x_max);
            p_err("Error");
        } while (err_code != SUCCESS);

        // Get higher bound of x
        do {
            err_code = SUCCESS;
            x_high = get_double(x_max_len, "Enter higher bound of x: ");
            if (err_code == SUCCESS) double_closed_range(x_high, x_low, x_max);
            p_err("Error");
        } while (err_code != SUCCESS);

        // Get step
        if (x_low == x_high) {
            step = 1.0;
        } else {
            do {
                err_code = SUCCESS;
                step = get_double(x_max_len, "Enter the step: ");
                if (err_code == SUCCESS) double_open_range(step, step_min, x_high);
                p_err("Error");
            } while (err_code != SUCCESS);
        }

        // Get term accuracy
        do {
            err_code = SUCCESS;
            term_acc = get_uint(acc_max_len, "Enter term accuracy: ");
            if (err_code == SUCCESS) uint_closed_range(term_acc, acc_min, acc_max);
            p_err("Error");
        } while (err_code != SUCCESS);

        // Get output accuracy
        do {
            err_code = SUCCESS;
            output_acc = get_uint(acc_max_len, "Enter output accuracy: ");
            if (err_code == SUCCESS) uint_closed_range(output_acc, acc_min, acc_max);
            p_err("Error");
        } while (err_code != SUCCESS);

        // Get function
        do {
            err_code = SUCCESS;
            str_func = get_str(str_func_len, "Enter a trigonometric function (sin, cos, tan, cot): ");
            if (err_code == SUCCESS) func = get_trig_func(str_func);
            p_err("Error");
        } while(err_code != SUCCESS);

        // Get function arrays with regular and taylor functions
        x = x_low;
        arr_size = (uint32_t)((x_high - x_low) / step) + 1;
        double taylor_func_array[arr_size];
        double reg_func_array[arr_size];
        switch (func) {
            case SIN:
                for(int i = 0; i < arr_size; i++) {
                    taylor_func_array[i] = taylor_sin(x, term_acc);
                    reg_func_array[i] = sin(deg_to_rad(x));
                    x += step;
                }
                break;
            case COS:
                for(int i = 0; i < arr_size; i++) {
                    taylor_func_array[i] = taylor_cos(x, term_acc);
                    reg_func_array[i] = cos(deg_to_rad(x));
                    x += step;
                }
                break;
            case TAN:
                for(int i = 0; i < arr_size; i++) {
                    taylor_func_array[i] = taylor_tan(x, term_acc);
                    reg_func_array[i] = tan(deg_to_rad(x));
                    x += step;
                }
                break;
            case COT:
                for(int i = 0; i < arr_size; i++) {
                    taylor_func_array[i] = taylor_cot(x, term_acc);
                    reg_func_array[i] = cos(deg_to_rad(x)) / sin(deg_to_rad(x));
                    x += step;
                }
                break;
        }

        // Print out the table
        printf("%-*s | %-*s | %s %-*s | %-*s\n",
               padding_size + 1, "x°",
               padding_size, str_func,
               "taylor", (uint32_t)(padding_size - strlen("taylor") - 1), str_func,
               padding_size, "error");

        x = x_low;
        for (int i = 0; i < arr_size; i++) {
            printf("%-*.*lf | %-*.*lf | %-*.*lf | %-*.*e\n",
                   padding_size, output_acc, x,
                   padding_size, output_acc, reg_func_array[i],
                   padding_size, output_acc, taylor_func_array[i],
                   padding_size, output_acc, fabs(reg_func_array[i] - taylor_func_array[i]));
            x += step;
        }

        free(str_func);
    } while (!get_exit());

    return EXIT_SUCCESS;
}