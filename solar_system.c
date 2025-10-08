#include "FPToolkit.c"
#include <math.h>

int main() {
    G_init_graphics(800, 800);

    double cx = 400, cy = 400;   // center of sun
    double r = 200;              // radius of Earth's orbit
    double a = 0;                // starting angle

    while (1) {
        // Draw background
        G_rgb(0, 0, 0);
        G_clear();

        // Draw the sun
        G_rgb(1, 1, 0);
        G_fill_circle(cx, cy, 50);

        // Calculate Earth’s position
        double x = r * cos(a) + cx;
        double y = r * sin(a) + cy;

        // Draw the Earth
        G_rgb(0, 0, 1);
        G_fill_circle(x, y, 20);

        // Wait for key before moving
        G_wait_key();

        // Increase angle to move Earth
        a += 0.2;  // controls orbit speed
    }

    return 0;
}
