// Nov 24, 2025

#include <stdio.h>
#include <math.h> 
#include <complex.h>
#include <stdlib.h> 
#include "FPToolkit.c"

// --- Function Prototype ---
complex double map_pixel_to_complex(int xp, int yp, double r);

int main()
{
    // --- Define the Roots (for f(z) = z^3 - 1 = 0) ---
    complex double r1 = 1.0 + 0.0 * I;                       // Root 1: 1
    complex double r2 = -0.5 + sqrt(3.0)/2.0 * I;            // Root 2: -0.5 + i*sqrt(3)/2
    complex double r3 = -0.5 - sqrt(3.0)/2.0 * I;            // Root 3: -0.5 - i*sqrt(3)/2
    
    // --- Graphics Setup ---
    const int D = 800; // Window size
    G_init_graphics(D, D);
    int max_iter = 50;
    double zoom_radius = 2.0; // The complex plane extends from -2 to +2

    G_clear();
    
    // --- Loop over every pixel (xp, yp) to draw the fractal ---
    for (int xp = 0; xp < D; xp++) {
        for (int yp = 0; yp < D; yp++) {
        
            // 1. Map pixel to complex plane (initial guess z0)
            complex double z = map_pixel_to_complex(xp, yp, zoom_radius);
        
            // 2. Iterate Newton-Raphson
            int k;
            for (k = 0; k < max_iter; k++) {
                
                // Newton-Raphson update for f(z) = z^3 - 1
                complex double numerator = cpow(z, 3) - 1.0;
                complex double denominator = 3.0 * cpow(z, 2);
                
                // Check if the derivative is too close to zero to prevent division by zero
                if (cabs(denominator) < 1e-12) {
                    k = max_iter; // Treat as non-convergent
                    break;
                }
                
                z = z - numerator / denominator;
                
                // 3. Check for convergence to a root
                if (cabs(z - r1) < 1e-6) {
                    G_rgb(0.5, 0.0, 0.5); // Purple (Root 1)
                    break;
                } else if (cabs(z - r2) < 1e-6) {
                    G_rgb(1.0, 0.0, 0.0); // Red (Root 2)
                    break;
                } else if (cabs(z - r3) < 1e-6) {
                    G_rgb(0.0, 0.0, 1.0); // Blue (Root 3)
                    break;
                }
            } // End of k loop
        
            // 4. Color the pixel
            if (k == max_iter) {
                G_rgb(0.0, 0.0, 0.0); // Black (Did not converge)
            }
            G_point(xp, yp);
        } // End of yp loop
    } // End of xp loop
    
    G_wait_key(); // Wait for user to close window
    return 0;
}


complex double map_pixel_to_complex(int xp, int yp, double r) {
    const double D_HALF = 400.0;
    
    // Maps pixel coordinates to complex coordinates centered at (0, 0)
    double x_real = r * (xp - D_HALF) / D_HALF;
    double y_imag = r * (yp - D_HALF) / D_HALF;
    
    return x_real + y_imag * I;
}