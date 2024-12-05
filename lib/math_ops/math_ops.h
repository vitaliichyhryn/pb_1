#pragma once

#include <stdlib.h>

bool is_even(double);
bool int_closed_range(int32_t, int32_t, int32_t);
bool int_open_range(int32_t, int32_t, int32_t);
bool uint_closed_range(uint32_t, uint32_t, uint32_t);
bool uint_open_range(uint32_t, uint32_t, uint32_t);
bool double_closed_range(double, double, double);
bool double_open_range(double, double, double);
size_t int_digit_count(int32_t);
size_t int_char_count(int32_t);
size_t fract_digit_count(double);
double nth_root(double, int32_t, int32_t);
bool jacobi_converges(double **, size_t);
double *jacobi_method(double **, double *, size_t, size_t);
double derivative(double (double, double), double, double);
double bisec_method(double (double, double), double, double, double, size_t);
double newton_method(double (double, double), double, double, size_t);