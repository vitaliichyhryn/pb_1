#pragma once

enum trig_func {
    SIN,
    COS,
    TAN,
    COT
};

enum trig_func get_trig_func(char*);

double deg_to_rad(double);

double taylor_sin(double, uint32_t);

double taylor_cos(double, uint32_t);

double taylor_tan(double, uint32_t);

double taylor_cot(double, uint32_t);