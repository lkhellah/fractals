// koch curve -> koch snowflake
#include "FPToolkit.c"
#include <math.h>

// Function declarations
void rotational_method(double x0, double y0, double x4, double y4, int depth);
void parametric_method(double x0, double y0, double x4, double y4, int depth);

int main()
{
    double x0 = 100, y0 = 300;
    double x4 = 500, y4 = 300;
    int depth = 4;

    G_init_graphics(800, 800);
    G_rgb(1, 1, 1);
    G_clear();

    // Choose which method to run:
    // -------------------------------------
    G_rgb(0, 0, 1); // blue — parametric
     parametric_method(x0, y0, x4, y4, depth);

    G_rgb(1, 0, 0); // red — rotational
    // rotational_method(x0, y0, x4, y4, depth);
    // -------------------------------------

    G_wait_key();
    return 0;
}

// ----------------------------------------------------
// METHOD 1: PARAMETRIC (perpendicular vector approach)
// ----------------------------------------------------
void parametric_method(double x0, double y0, double x4, double y4, int depth)
{
    if (depth == 0)
    {
        G_line(x0, y0, x4, y4);
        return;
    }

    // Step 1: divide line into thirds
    double x1 = x0 + (x4 - x0) / 3.0;
    double y1 = y0 + (y4 - y0) / 3.0;
    double x2 = x0 + 2.0 * (x4 - x0) / 3.0;
    double y2 = y0 + 2.0 * (y4 - y0) / 3.0;

    // Step 2: find the triangle peak (perpendicular vector)
    double dx = x2 - x1;
    double dy = y2 - y1;
    double angle = M_PI / 3.0; // 60 degrees

    // Rotate dx, dy by +60 degrees
    double x3 = x1 + dx * cos(angle) - dy * sin(angle);
    double y3 = y1 + dx * sin(angle) + dy * cos(angle);

    // Recursive calls for the 4 segments
    parametric_method(x0, y0, x1, y1, depth - 1);
    parametric_method(x1, y1, x3, y3, depth - 1);
    parametric_method(x3, y3, x2, y2, depth - 1);
    parametric_method(x2, y2, x4, y4, depth - 1);
}

// ----------------------------------------------------
// METHOD 2: ROTATIONAL (explicit rotation transformations)
// ----------------------------------------------------
void rotational_method(double x0, double y0, double x4, double y4, int depth)
{
    if (depth == 0)
    {
        G_line(x0, y0, x4, y4);
        return;
    }

    // Divide the segment into thirds
    double x1 = x0 + (x4 - x0) / 3.0;
    double y1 = y0 + (y4 - y0) / 3.0;
    double x2 = x0 + 2.0 * (x4 - x0) / 3.0;
    double y2 = y0 + 2.0 * (y4 - y0) / 3.0;

    // Compute the rotated peak using explicit transformation
    double dx = x2 - x1;
    double dy = y2 - y1;
    double angle = M_PI / 3.0;

    // Rotate (dx, dy) by +60° around (x1, y1)
    double x3 = x1 + dx * cos(angle) - dy * sin(angle);
    double y3 = y1 + dx * sin(angle) + dy * cos(angle);

    // Recurse on the 4 new segments
    rotational_method(x0, y0, x1, y1, depth - 1);
    rotational_method(x1, y1, x3, y3, depth - 1);
    rotational_method(x3, y3, x2, y2, depth - 1);
    rotational_method(x2, y2, x4, y4, depth - 1);
}
