#include "FPToolkit.c"
#include <complex.h>
#include <math.h>
#include <stdio.h>

// Mandelbrot set
//  Nov 17, 2025
// adjusting to include: xc_bar, yc_bar, r_bar
/*
    clicking ping pong between both worlds: pixel and complex world
    yp-400/400 = y -yc/r
    double p[2];
    G_wait_click(p);
    xp = p[0];
    yp=p[1];
    redraw picture with new center and new radius 
    r = sqrt[] (x2-x)^2 + (y2 - y^)^2 ]

*/

int main()
{
    int width = 800, height = 800;
    complex z, c;

    double x, y, xp, yp, k, r, xc, yc;


    G_init_graphics(width, height);
    G_rgb(0, 0, 0);
    G_clear();
    double max = 10;
    int numreps = 10;    // number of iterations per point
    double maxabs = 4.0; // threshold for divergence

    c = I;
    r = 2;
    xc = 0;
    yc = 0;
    // Loop over every pixel
    for (xp = 0; xp < width; xp++)
    {
        for (yp = 0; yp < height; yp++)
        {
            x = xc + r * (xp - 400) / 400;
            y = yc + r * (yp - 400) / 400;
            z = 0;
            for (k = 0; k < numreps; k++)
            {
                z = z * z + (x + y * I);
                if (cabs(z) > maxabs)
                {
                    break;
                }
            }
            if (k == numreps)
            {
                // playing around with coloring
                double w = cabs(z) / maxabs;
                G_rgb(1, 0, w);
            }
            else
            {
                // another way to color
                double v = 1.0 * k / numreps;
                G_rgb(v, v, v);
            }
            G_point(xp, yp);
        }
    }

    G_wait_key();
    return 0;
}
