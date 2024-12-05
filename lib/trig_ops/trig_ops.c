#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "err.h"

enum trig_func {
    SIN,
    COS,
    TAN,
    COT
};

enum trig_func get_trig_func(char *str) {
    if (strcasecmp(str, "sin") == 0) {
        return SIN;
    } else if (strcasecmp(str, "cos") == 0) {
        return COS;
    } else if (strcasecmp(str, "tan") == 0) {
        return TAN;
    } else if (strcasecmp(str, "cot") == 0) {
        return COT;
    } else {
        err_code = NOT_TRIG_FUNC;
        return 0;
    }
}

double deg_to_rad(double deg_val) {
    return deg_val * (M_PI / 180.0);
}

double taylor_sin(double x, uint32_t acc) {
    x = remainder(x, 360.0);
    x = deg_to_rad(x);
    double real_accuracy = pow(0.1, acc);
    double n = 1.0;
    double term = x;
    double sin = x;

    do {
        term *= -(x * x) / ((n + 1.0) * (n + 2.0));
        sin += term;
        n += 2.0;
    } while (fabs(term) >= real_accuracy);

    return sin;
}

double taylor_cos(double x, uint32_t acc) {
    x = remainder(x, 360.0);
    x = deg_to_rad(x);
    double real_accuracy = pow(0.1, acc);
    double n = 1.0;
    double term = 1.0;
    double cos = 1.0;

    do {
        term *= -(x * x) / (2.0 * n * (2.0 * n - 1.0));
        cos += term;
        n += 1.0;
    } while (fabs(term) >= real_accuracy);

    return cos;
}

double taylor_tan(double x, uint32_t acc) {
    x = remainder(x, 180.0);
    if (remainder(x + 90.0, 180.0) == 0.0) {
        return NAN;
    } else {
        return taylor_sin(x, acc) / taylor_cos(x, acc);
    }
}

double taylor_cot(double x, uint32_t acc) {
    x = remainder(x, 180.0);
    if (remainder(x, 180.0) == 0.0) {
        return NAN;
    } else {
        return taylor_cos(x, acc) / taylor_sin(x, acc);
    }
}