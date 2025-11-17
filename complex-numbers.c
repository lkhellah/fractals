#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>



void pcmx(complex w);

int main()
{
    complex a,b,c,d,e,f;
    double S;

    a = 3 + 4*I;
    b = 2 - S*I;
    c =a + b;
    d = a-b;
    e = a * b;
    f = e/a;
    pcmx(a);
    pcmx(b);

}

void pcmx(complex w) {
    double rp, ip;
    rp = creal(w);
    ip = cimag(w);
    if (ip < 0) {
        printf("%lf - %lfI", rp, -ip);
        printf("%lf + %lfI", rp, ip);

    }

}
