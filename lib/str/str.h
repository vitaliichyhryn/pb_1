#pragma once

char *trim(char*);

bool ends_on_newline(char*);

bool is_whitespace(char*);

bool has_sign(char*);

bool is_int(char*);

bool is_uint(char*);

bool is_double(char*);

size_t str_fract_len(char*);

int32_t p_str_cmp(const void*, const void*);