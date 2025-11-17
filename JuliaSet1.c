#include "FPToolkit.c"
#include <complex.h>
#include <math.h>
#include <stdio.h>

// Goal: visualize whether points in the complex plane go to infinity or 0 
// under z_{n+1} = z^2 + i
// displays a lightning bolt

int main() {
    int width = 800, height = 800;
    complex z;
    double x,y, xp, yp;
    
    G_init_graphics(width, height);
    G_rgb(0, 0, 0);
    G_clear();
    
    // Loop over every pixel
    for (xp = 0; xp < width; xp++) {
        for ( yp = 0; yp < height; yp++) {
            x = (xp-400)/200;
            y = (yp-400)/200;
            z = x + y*I;
            for (int j = 0; j < 10; j++) {
                z = cpow(z,2) + I;
            }
            if (cabs(z) > 1) {
                G_rgb(0,0,0);
            }
            else {
                G_rgb(1,1,1);
            }
            xp = 200*x + 400;
            yp = 200*y + 400;
            G_point(xp, yp);
        }
    }

    G_wait_key();
    return 0;
}
