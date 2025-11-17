#include "FPToolkit.c"
#include <complex.h>
#include <math.h>
#include <stdio.h>

int main() {
    int width = 800, height = 800;
    int numreps = 100;
    double maxabs = 4.0;
    double r = 2.0;   // radius of complex plane window

    // List of c values
    complex cvals[] = {
        -0.8 + 0.156*I,
        -0.7269 + 0.1889*I,
        -0.835 - 0.2321*I,
        -0.70176 - 0.3842*I
    };

    int num_c = 4;

    G_init_graphics(width, height);
    G_rgb(0, 0, 0);
    G_clear();

    // Draw each Julia set in a quadrant
    for (int ci = 0; ci < num_c; ci++) {
        complex c = cvals[ci];

        // compute offset for quadrant placement
        int xoff = (ci % 2) * (width/2);
        int yoff = (ci / 2) * (height/2);

        for (int xp = 0; xp < width/2; xp++) {
            for (int yp = 0; yp < height/2; yp++) {
                
                // Convert pixel → complex plane
                double x = r * ( (double)xp - (width/4) ) / (width/4);
                double y = r * ( (double)yp - (height/4) ) / (height/4);
                complex z = x + y*I;

                int k;
                for (k = 0; k < numreps; k++) {
                    z = z*z + c;
                    if (cabs(z) > maxabs) break;
                }

                double red, green, blue;

                if (k == numreps) {
                    // inside = black/purple
                    double w = cabs(z) / maxabs;
                    red = w;
                    green = 0;
                    blue = w;
                } else {
                    // escaped → grayscale
                    double v = (double)k / numreps;
                    red = v; green = v; blue = v;
                }

                G_rgb(red, green, blue);
                G_point(xp + xoff, yp + yoff);
            }
        }
    }

    G_wait_key();
    return 0;
}
