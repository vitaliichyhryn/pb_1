#include <stdio.h>

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

const char* get_err_str() {
    switch(err_code) {
        case SUCCESS:
            return "No error";
        case STR_OVERFLOW:
            return "String is larger than the allocated memory";
        case NOT_INT:
            return "String is not an integer number";
        case NOT_UINT:
            return "String is not an unsigned integer number";
        case NOT_FLOAT:
            return "String is not a floating point number";
        case NOT_IN_RANGE:
            return "Value is not in range";
        case NOT_AN_OPTION:
            return "Not an option";
        case NOT_TRIG_FUNC:
            return "String is not a trigonometric function";
        case NO_CONVERGENCE:
            return "Method doesn't converge";
        case ILLEGAL_NAME:
            return "Illegal name";
    }
}

void clr_err() {
    err_code = SUCCESS;
}

void p_err(char* str, enum p_err_mode mode) {
    const char *err_str = get_err_str();

    switch (mode) {
        case QUIET: {
            if (err_code != SUCCESS) {
                fprintf(stderr, "%s%s\n", str, err_str);
            }
            break;
        }
        case LOUD: {
            fprintf(stderr, "%s%s\n", str, err_str);
            break;
        }
    }
}