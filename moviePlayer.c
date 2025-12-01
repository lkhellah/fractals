// Nov 19, 2025

#include "FPToolkit.c"
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h> // Needed for the usleep function


void movie(int s, int e);

int main()
{
    int start_frame = 0;
    int end_frame = 100;
    G_init_graphics(800, 800);
    movie(start_frame, end_frame);
    // Wait for a key press before closing the window
    G_wait_key();
    return 0;
}

void movie (int s, int e) 
{
    char fname[100];
    int count = 0;
    
    // Loop from the start frame (s) to the end frame (e)
    for (count = s; count <= e; count++) {
        // Construct the filename (e.g., "mand0000.bmp")
        sprintf(fname, "mand%04d.bmp", count);
        
        printf("Displaying frame: %s\n", fname); 
        
        // Load and display the image file 
        // Display the image at pixel location (0, 0)
        if (G_display_bmp_file(fname, 0, 0) == 0) {
            printf("Error: File %s not found. Stopping playback.\n", fname);
            break; 
        }
        
        // Pause the program for 40,000 microseconds (0.04 seconds)
        usleep(40000); 
    }
}