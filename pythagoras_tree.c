#include "FPToolkit.c"
#include <math.h>

// M_PI is often defined in math.h, but let's define it explicitly for robustness
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Function to draw the tree
// x, y: bottom-left corner of the current square
// s: side length of the current square
// angle: orientation angle of the square in radians (0 for horizontal)
// depth: recursion depth
void draw_tree(double x, double y, double s, double angle, int depth);

// (main function remains the same, but the call to draw_tree needs the angle)
int main () {

    G_init_graphics(800, 800);
    G_rgb(0.9, 0.9, 0.9);
    G_clear();

    double x = 350;  // bottom-left of trunk square
    double y = 50;   // start near bottom
    double s = 100;  // initial square size
    double angle = 0.0; // Initial angle is 0 (horizontal base)
    int depth = 10;   // Increased depth for better visual

    G_rgb(0, 0.5, 0); // dark green for tree
    draw_tree(x, y, s, angle, depth);

    G_wait_key();
    return 0;
}

// draw the current square and recursively grow two smaller ones on top
void draw_tree(double x, double y, double s, double angle, int depth)
{
    if (depth == 0) return;

    // --- 1. Calculate the four corners of the current square ---

    // Define the corners relative to (x, y) if angle was 0
    // (x0, y0) = (x, y) - bottom-left
    // (x1, y1) = (x + s, y) - bottom-right
    // (x2, y2) = (x + s, y + s) - top-right
    // (x3, y3) = (x, y + s) - top-left

    // Use rotation formulas to find the actual coordinates (x_rotated, y_rotated)
    // x' = x*cos(a) - y*sin(a)
    // y' = x*sin(a) + y*cos(a)

    double c = cos(angle);
    double ss = sin(angle); // 'ss' to avoid conflict with 's' for side length

    // Corner 0: (x0, y0) - bottom-left (is the input x, y)
    double x0 = x;
    double y0 = y;

    // Corner 1: (x1, y1) - bottom-right
    double dx1 = s; double dy1 = 0;
    double x1 = x + dx1 * c - dy1 * ss;
    double y1 = y + dx1 * ss + dy1 * c;

    // Corner 2: (x2, y2) - top-right
    double dx2 = s; double dy2 = s;
    double x2 = x + dx2 * c - dy2 * ss;
    double y2 = y + dx2 * ss + dy2 * c;

    // Corner 3: (x3, y3) - top-left
    double dx3 = 0; double dy3 = s;
    double x3 = x + dx3 * c - dy3 * ss;
    double y3 = y + dx3 * ss + dy3 * c;


    // --- 2. Draw the square ---
    G_rgb(0, 0.5, 0); // dark green
    G_line(x0, y0, x1, y1);
    G_line(x1, y1, x2, y2);
    G_line(x2, y2, x3, y3);
    G_line(x3, y3, x0, y0);


    // --- 3. Calculate the peak (x4, y4) of the right triangle ---
    // The peak forms a 45-degree angle with the top side (x3, y3) to (x2, y2).
    // The new side lengths are s/sqrt(2), and the angle is 45 degrees relative to the top side.
    double new_s = s / sqrt(2.0);

    // Vector from x3 to x2
    double dx_top = x2 - x3;
    double dy_top = y2 - y3;

    // The peak (x4, y4) is found by rotating the vector (dx_top, dy_top) by -45 degrees
    // (or angle + pi/4) and scaling it to the new side length.
    // The peak is (x3, y3) + vector rotated by -45 degrees, which is the standard 90 degree triangle construction.
    // The angle of the vector (x3->x2) is simply the current angle.
    // The angle of the left side of the triangle is angle + M_PI/2.
    // The peak is (x4, y4) = (x3, y3) + vector of length 'new_s' at angle 'angle + M_PI/4'

    double peak_angle = angle + M_PI / 4.0;
    double x4 = x3 + new_s * cos(peak_angle);
    double y4 = y3 + new_s * sin(peak_angle);

    // --- 4. Draw triangle roof ---
    G_rgb(0.3, 0.7, 0.3); // lighter green
    G_line(x3, y3, x4, y4);
    G_line(x2, y2, x4, y4);


    // --- 5. Recursive calls for the two smaller squares ---

    // The new side length is s/sqrt(2)
    // The new squares' base corners are (x3, y3) and (x4, y4) respectively.

    // Left smaller square (sits on the side (x3, y3) to (x4, y4))
    // The square is built on the hypotenuse of the left new right triangle.
    // New angle: angle + M_PI/4 (45 degrees clockwise relative to the parent's top)
    draw_tree(x3, y3, new_s, angle + M_PI / 4.0, depth - 1);

    // Right smaller square (sits on the side (x4, y4) to (x2, y2))
    // New angle: angle - M_PI/4 (45 degrees counter-clockwise relative to the parent's top)
    draw_tree(x4, y4, new_s, angle - M_PI / 4.0, depth - 1);
}