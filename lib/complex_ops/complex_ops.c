#include <stdio.h>
#include <stdlib.h>

#include <math.h>

typedef struct {
    double rl;
    double im;
} comp;

void pcomp(char *str, comp x, uint32_t output_acc) {
    if (x.im < 0) {
        printf("%s%.*e - %.*e * i\n", str, output_acc, x.rl, output_acc, fabs(x.im));
    } else {
        printf("%s%.*e + %.*e * i\n", str, output_acc, x.rl, output_acc, x.im);
    }
}

comp fract_comp(comp x, comp y) {
    comp fract;

    fract.rl = (x.rl * y.rl + x.im * y.im) /
               (y.rl * y.rl + y.im * y.im);
    fract.im = (x.im * y.rl - x.rl * y.im) /
               (y.rl * y.rl + y.im * y.im);

    return fract;
}