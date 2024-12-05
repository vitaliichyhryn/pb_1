#pragma once

enum mode {
    NO_MODE,
    MANUAL,
    RANDOM
};

enum method {
    NO_METHOD,
    BISEC,
    NEWTON
};

int64_t get_int(size_t, char *);
uint64_t get_uint(size_t, char *);
double get_double(size_t, char *);
char *get_str(size_t, char *);
enum mode get_mode();
enum method get_root_find_method();
bool get_exit();
void free_p_arr(void **, size_t);