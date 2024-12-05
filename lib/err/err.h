#pragma once

enum err {
    SUCCESS,
    STR_OVERFLOW,
    NOT_INT,
    NOT_UINT,
    NOT_FLOAT,
    NOT_IN_RANGE,
    NOT_AN_OPTION,
    NOT_TRIG_FUNC,
    NO_CONVERGENCE,
    ILLEGAL_NAME
};

enum p_err_mode {
    QUIET,
    LOUD
};

enum err err_code;
char *get_err_str();
void clr_err();
void p_err(char *, enum p_err_mode);