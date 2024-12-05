#include <math.h>
#include <stdlib.h>

#include "err.h"

bool is_even(double x) {
    return remainder(x, 2.0) == 0;
}

bool int_closed_range(int32_t num, int32_t min, int32_t max) {
    if (num >= min && num <= max) {
        return true;
    } else {
        err_code = NOT_IN_RANGE;
        return false;
    }
}

bool int_open_range(int32_t num, int32_t min, int32_t max) {
    if (num > min && num < max) {
        return true;
    } else {
        err_code = NOT_IN_RANGE;
        return false;
    }
}

bool uint_closed_range(uint32_t num, uint32_t min, uint32_t max) {
    if (num >= min && num <= max) {
        return true;
    } else {
        err_code = NOT_IN_RANGE;
        return false;
    }
}

bool uint_open_range(uint32_t num, uint32_t min, uint32_t max) {
    if (num > min && num < max) {
        return true;
    } else {
        err_code = NOT_IN_RANGE;
        return false;
    }
}

bool double_closed_range(double num, double min, double max) {
    if (num >= min && num <= max) {
        return true;
    } else {
        err_code = NOT_IN_RANGE;
        return false;
    }
}

bool double_open_range(double num, double min, double max) {
    if (num > min && num < max) {
        return true;
    } else {
        err_code = NOT_IN_RANGE;
        return false;
    }
}

size_t int_digit_count(int32_t num) {
    if (num < 0)
        return int_digit_count((num == INT32_MIN) ? INT32_MAX : -num);
    if (num < 10)
        return 1;
    return 1 + int_digit_count(num / 10);
}

size_t int_char_count(int32_t num) {
    return num < 0 ? int_digit_count(num) + 1 : int_digit_count(num);
}

size_t fract_digit_count(double num) {
    for (int i = 0;; i++) {
        if (pow(10.0, i) * num == floor(pow(10.0, i) * num)) {
            return i;
        }
    }
}

double nth_root(double x, int32_t n, int32_t acc) {
    double last_iter = 1.0;
    double cur_iter = last_iter;
    double real_acc = pow(0.1, acc);

    do {
        last_iter = cur_iter;
        cur_iter = ((fabs((double)n) - 1.0) / fabs((double)n)) * last_iter +
                   (x / fabs((double)n)) * (1.0 / pow(last_iter, fabs((double)n) - 1.0));
    } while (fabs(cur_iter - last_iter) > real_acc);

    if (n < 0) {
        return (1.0 / cur_iter);
    } else {
        return cur_iter;
    }
}

bool jacobi_converges(double **a, size_t x_num) {
    double sum;
    for (size_t i = 0; i < x_num; ++i) {
        sum = 0.0;
        for (size_t j = 0; j < x_num; ++j) {
            if (i != j) {
                sum += a[i][j];
            }
        }
        if (a[i][i] < sum) {
            err_code = NO_CONVERGENCE;
            return false;
        }
    }
    return true;
}

double *jacobi_method(const double **a, const double *b, size_t x_num, size_t calc_acc) {
    double real_acc = pow(0.1, (double)calc_acc);
    double calc_err;

    double *x = (double*)calloc(x_num, sizeof(double));
    double *old_x = (double*)calloc(x_num, sizeof(double));
    double sum;

    do {
        calc_err = 0.0;
        for (size_t i = 0; i < x_num; ++i) {
            sum = 0.0;
            for (size_t j = 0; j < x_num; ++j) {
                if (i != j) {
                    sum += a[i][j] * old_x[j];
                }
            }
            x[i] = (b[i] - sum) / a[i][i];
            calc_err = fabs(x[i] - old_x[i]);
            old_x[i] = x[i];
        }
    } while (calc_err > real_acc);

    free(old_x);

    return x;
}

double derivative(double f(double, double), double x, double n) {
    const double h = 1e-9;
    return (f(x + h, n) - f(x, n)) / h;
}

double bisec_method(double f(double, double), double n, double a, double b, size_t calc_acc) {
    double real_acc = pow(0.1, (double)calc_acc);
    double x;

    do {
        x = (a + b) / 2.0;
        if (f(a, n) * f(x, n) > 0) {
            a = x;
        } else {
            b = x;
        }

        if ((f(a, n) >= 0) ^ (f(b, n) < 0)) {
            err_code = NO_CONVERGENCE;
            return 0;
        }
    } while(fabs(b - a) > real_acc);

    return x;
}

double newton_method(double f(double, double), double x0, double n, size_t calc_acc) {
    double real_acc = pow(0.1, (double)calc_acc);
    double x = x0;
    const int32_t i_max = 1024;

    for (int i = 0; i < i_max; i++) {
        x = x - f(x, n) / derivative(f, x, n);
        if (fabs(f(x, n) / derivative(f, x, n)) < real_acc) {
            return x;
        }
    }

    err_code = NO_CONVERGENCE;
    return 0;
}