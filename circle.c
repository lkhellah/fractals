#include "FPToolkit.c"
#include <math.h>

int main() {
    G_init_graphics(800, 800);

    double cx = 400, cy = 400;  // center of circle
    double r = 200;             // radius

    G_rgb(0, 0, 1);  // blue

    // This loop rotates the angle 'a' from 0 to 2π in small steps (0.001 radians)
    // plotting each (x, y) point from r*cos(a) and r*sin(a) to trace a smooth circle.
    for (double a = 0; a <= 2*M_PI; a += 0.001) {
        double x = r * cos(a) + cx;
        double y = r * sin(a) + cy;
        G_point(x, y);
    }

    G_wait_key();
    return 0;
}
