#include "FPToolkit.c"
#include <complex.h>
#include <math.h>
#include <stdio.h>

// Mandelbrot set
//  Nov 17, 2025
// adjusting to include: xc_bar, yc_bar, r_bar

void Mandelbrot(double xc, double yc, double r, int numreps, double maxabs);

int main()
{
    // Define window size for consistent calculations
    const double D_HALF = 400.0;
    
    G_init_graphics(800, 800);
    double xc = 0; 
    double yc = 0;
    double r = 2;
    double p[2], q[2];
    int numreps = 50;    // number of iterations per point
    double maxabs = 2.0; // threshold for divergence
    int done = 0;
    
    // file saving variables
    int count = 0;
    char fname[100];

   while(!done) {
        G_clear();
        Mandelbrot(xc, yc, r, numreps, maxabs);
        
        // File saving logic:
        // 1. Create the filename (e.g., "mand0001.bmp")
        sprintf(fname, "mand%04d.bmp", count);
        
        // 2. Save the currently drawn frame to the file
        G_save_to_bmp_file(fname);
        
        // 3. Increment the counter for the next file
        count++;
        
        printf("Saved: %s. Current center: (%.6f, %.6f), Radius: %.6f\n", fname, xc, yc, r);
        printf("Click the center of the new view (p).\n");
        G_wait_click(p);
        printf("Click a point to define the new radius (q).\n");
        G_wait_click(q);
        
        
        // Convert p (Pixel) to p (Complex)
        p[0] = xc + r * (p[0] - D_HALF) / D_HALF;
        p[1] = yc + r * (p[1] - D_HALF) / D_HALF;
        
        // Convert q (Pixel) to q (Complex)
        q[0] = xc + r * (q[0] - D_HALF) / D_HALF;
        q[1] = yc + r * (q[1] - D_HALF) / D_HALF;
        
        // Calculate new radius (r) using the distance formula
        double dx = q[0] - p[0];
        double dy = q[1] - p[1];
        r = sqrt(dx * dx + dy * dy); 
        
        // Set new center
        xc = p[0];
        yc = p[1];
        
        // Increase the number of reps for deeper zooming
        numreps += 50;
   }

    // This G_wait_key() is now only reached if 'done' is manually set to 1
    // or if the program is externally terminated (e.g., Ctrl+C).
    G_wait_key(); 
    return 0;
}


void Mandelbrot(double xc, double yc, double r, int numreps, double maxabs) {
    // Loop over every pixel
    complex double z, cpix; // Use complex double for safety
    double x, y, xp, yp;
    int k;
    for (xp = 0; xp < 800; xp++)
    {
        for (yp = 0; yp < 800; yp++)
        {
            x = xc + r * (xp - 400.0) / 400.0;
            y = yc + r * (yp - 400.0) / 400.0;
            cpix = x + I*y;
            z = 0;
            for (k = 0; k < numreps; k++)
            {
                z = z * z + cpix;
                if (cabs(z) > maxabs)
                {
                    break;
                }
            }
            if (k == numreps)
            {
                // Inside set: White
                G_rgb(1.0, 1.0, 1.0); 
            }
            else
            {
                // Outside set: Coloring based on iteration count for detail
                double intensity = (double)k / (double)numreps; 
                // Using a color gradient (e.g., dark to bright blue)
                G_rgb(0.0, 0.0, 0.2 + intensity * 0.8);
            }
            G_point(xp, yp);
        }
    }
}