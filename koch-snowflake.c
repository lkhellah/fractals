// koch_snowflake.c
// Builds on koch_curve.c — only changes are in main()

#include "FPToolkit.c"
#include <math.h>

void rotational_method(double x0, double y0, double x4, double y4, int depth);
void parametric_method(double x0, double y0, double x4, double y4, int depth);

int main()
{
    // --- CHANGE 1: window color / background same ---
    G_init_graphics(800, 800);
    G_rgb(1, 1, 1);
    G_clear();

    // --- CHANGE 2: coordinates form an equilateral triangle base ---
    double x0 = 200, y0 = 200;
    double x1 = 600, y1 = 200;
    double x2 = 400, y2 = 200 + (sqrt(3) / 2.0) * 400; // top vertex

    int depth = 4;

    // --- CHANGE 3: draw 3 Koch curves (snowflake sides) ---
    G_rgb(0, 0, 1); // color blue

    // Comment out one method if you want to test only one
     parametric_method(x0, y0, x1, y1, depth);
     parametric_method(x1, y1, x2, y2, depth);
     parametric_method(x2, y2, x0, y0, depth);

   // rotational_method(x0, y0, x1, y1, depth);
    // rotational_method(x1, y1, x2, y2, depth);
    // rotational_method(x2, y2, x0, y0, depth);

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

    double x1 = x0 + (x4 - x0) / 3.0;
    double y1 = y0 + (y4 - y0) / 3.0;
    double x2 = x0 + 2.0 * (x4 - x0) / 3.0;
    double y2 = y0 + 2.0 * (y4 - y0) / 3.0;

    double dx = x2 - x1;
    double dy = y2 - y1;
    double angle = M_PI / 3.0; // 60 degrees

    double x3 = x1 + dx * cos(angle) - dy * sin(angle);
    double y3 = y1 + dx * sin(angle) + dy * cos(angle);

    parametric_method(x0, y0, x1, y1, depth - 1);
    parametric_method(x1, y1, x3, y3, depth - 1);
    parametric_method(x3, y3, x2, y2, depth - 1);
    parametric_method(x2, y2, x4, y4, depth - 1);
}

// ----------------------------------------------------
// METHOD 2: ROTATIONAL (explicit transformation)
// ----------------------------------------------------
void rotational_method(double x0, double y0, double x4, double y4, int depth)
{
    if (depth == 0)
    {
        G_line(x0, y0, x4, y4);
        return;
    }

    double x1 = x0 + (x4 - x0) / 3.0;
    double y1 = y0 + (y4 - y0) / 3.0;
    double x2 = x0 + 2.0 * (x4 - x0) / 3.0;
    double y2 = y0 + 2.0 * (y4 - y0) / 3.0;

    double dx = x2 - x1;
    double dy = y2 - y1;
    double angle = M_PI / 3.0;

    double x3 = x1 + dx * cos(angle) - dy * sin(angle);
    double y3 = y1 + dx * sin(angle) + dy * cos(angle);

    rotational_method(x0, y0, x1, y1, depth - 1);
    rotational_method(x1, y1, x3, y3, depth - 1);
    rotational_method(x3, y3, x2, y2, depth - 1);
    rotational_method(x2, y2, x4, y4, depth - 1);
}
