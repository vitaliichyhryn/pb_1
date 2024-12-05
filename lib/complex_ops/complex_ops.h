#pragma once

#include <stdlib.h>

typedef struct {
    double rl;
    double im;
} comp;

void pcomp(char *, comp, uint32_t);

comp fract_comp(comp, comp);