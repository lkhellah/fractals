// koch curve -> koch snowlflake
#include "FPToolkit.c"
#include <math.h>


void rotational_method(double a, double xr, double yr);
void parametric_method();
void translate(double tx, double ty);
void rotate(double a);

double x, y; //global


int main () {
    double a, xr, yr;
    rotational_method(a, xr, yr);

    return 0;
}

// FIRST METHOD: ROTATIONAL
void rotational_method (double a, double xr, double yr) {
    translate(-xr, -yr);
    rotate(a);
    translate(xr, yr);
    

}


void translate(double tx, double ty) {
    x = x + tx;
    y = y + ty;
}

void rotate(double a) {

}

// SECOND METHOD: PARAMETRIC + PERPENDICULAR VECTOR METHOD
void parametric_method() {}
