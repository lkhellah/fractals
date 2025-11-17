#include "FPToolkit.c"
#include <complex.h>
#include <math.h>
#include <stdio.h>

// Goal: visualize whether points in the complex plane go to infinity or 0 
// under z_{n+1} = z^2 + i
// displays a lightning bolt
// version 3: Nov 17, 2025

int main() {
    int width = 800, height = 800;
    complex z, c;
   
    double x,y, xp, yp,k, r;
    
    G_init_graphics(width, height);
    G_rgb(0, 0, 0);
    G_clear();
    double max = 10;
    int numreps = 10;    // number of iterations per point
    double maxabs = 4.0;  // threshold for divergence

    c = I;
    r = 2;
    // Loop over every pixel
    for (xp = 0; xp < width; xp++) {
        for ( yp = 0; yp < height; yp++) {
            x = x*c + r *(xp-400)/400;
            y = y*c + r *(yp-400)/400;
            z = x + y*I;
            for (k = 0; k < numreps; k++) {
                z = z*z + c;
                if(cabs(z) > maxabs){
                    break;
                } 
            }
            if (k == numreps ) {
                double w = cabs(z) / maxabs;
                G_rgb(1,0,w); 
            }
            else {
                double v = 1.0*k/numreps;
                G_rgb(v,v,v); 
            }
        
            G_point(xp, yp);
        }
    }

    G_wait_key();
    return 0;
}
