// This file demonstrates how to apply scaling and rotation to a point (x, y)
// relative to a center point (c_x, c_y)

#include <stdio.h>
#include <math.h>
#include "FPToolkit.c"

// M_PI is often defined in math.h, but we define it here for robustness
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Global point coordinates to be transformed
double g_x = 0.0;
double g_y = 0.0;


// Utility function to set the global point
void set_point(double initial_x, double initial_y)
{
    g_x = initial_x;
    g_y = initial_y;
}


// Applies rotation only (relative to the origin (0, 0))
void rotate(double angle_degrees)
{
    // Convert angle to radians
    double rad = angle_degrees * M_PI / 180.0;
    
    // Store original coordinates before modification
    double temp_x = g_x;
    
    // Rotation formulas: x' = x*cos(a) - y*sin(a)
    g_x = temp_x * cos(rad) - g_y * sin(rad);
    // Rotation formulas: y' = x*sin(a) + y*cos(a)
    g_y = temp_x * sin(rad) + g_y * cos(rad);
}


// Applies scaling only (relative to the origin (0, 0))
void scale(double sfx, double sfy) 
{
    g_x = sfx * g_x;
    g_y = sfy * g_y;
}


// Applies translation (simple addition)
void translate(double dx, double dy) 
{
    g_x += dx;
    g_y += dy;
}


int main(void) 
{
    // Define the center of rotation/scaling and transformation factors
    double cx = 400.0;  // Center X
    double cy = 400.0;  // Center Y
    double sfx = 2.0;   // Scale Factor X
    double sfy = 0.5;   // Scale Factor Y
    double angle = 90.0; // Rotation Angle (in degrees)
    
    // Starting point P (relative to the origin)
    double px = 50.0;
    double py = 100.0;

    printf("--- 2D Transformation Demonstration ---\n");
    printf("Center of Transformation (cx, cy): (%.1f, %.1f)\n", cx, cy);

    // ------------------------------------------------
    // DEMONSTRATE ROTATION AROUND A CENTER POINT
    // ------------------------------------------------
    
    // 1. Set the initial point P
    set_point(px, py);
    printf("\nStarting Point: (%.1f, %.1f)\n", g_x, g_y);

    // 2. Translate P so that the center (cx, cy) moves to the origin (0, 0)
    translate(-cx, -cy);
    printf("1. Translate to origin: (%.1f, %.1f)\n", g_x, g_y);
    
    // 3. Rotate P around the origin
    rotate(angle);
    printf("2. Rotate %.1f degrees: (%.1f, %.1f)\n", angle, g_x, g_y);
    
    // 4. Translate P back to the center position
    translate(cx, cy);
    printf("3. Translate back to center: (%.1f, %.1f)\n", g_x, g_y);
    printf("Result of Rotation around Center: (%.1f, %.1f)\n", g_x, g_y);


    // ------------------------------------------------
    // DEMONSTRATE SCALING AROUND A CENTER POINT
    // ------------------------------------------------

    // 1. Set the initial point P again
    set_point(px, py);
    printf("\nStarting Point: (%.1f, %.1f)\n", g_x, g_y);

    // 2. Translate P to origin (0, 0)
    translate(-cx, -cy);
    printf("1. Translate to origin: (%.1f, %.1f)\n", g_x, g_y);
    
    // 3. Scale P around the origin
    scale(sfx, sfy);
    printf("2. Scale by (%.1f, %.1f): (%.1f, %.1f)\n", sfx, sfy, g_x, g_y);
    
    // 4. Translate P back to the center position
    translate(cx, cy);
    printf("3. Translate back to center: (%.1f, %.1f)\n", g_x, g_y);
    printf("Result of Scaling around Center: (%.1f, %.1f)\n", g_x, g_y);

    return 0;
}
