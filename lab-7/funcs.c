#include <math.h>

#include "err.h"

double f1(double x, double n) {
    return cos(n / x) - 2 * sin(1 / x) + 1 / x;
}

bool dom_f1(double x) {
    if (x != 0) {
        return true;
    } else {
        err_code = NOT_IN_RANGE;
        return false;
    }
}

double f2(double x, double n) {
    return sin(log(x)) - cos(log(x)) + n * log(x);
}

bool dom_f2(double x) {
    if (x > 0) {
        return true;
    } else {
        err_code = NOT_IN_RANGE;
        return false;
    }
}