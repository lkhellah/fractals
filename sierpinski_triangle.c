#include "FPToolkit.c"
#include <math.h>

void triangle(double x0, double y0, double x1, double y1, double x2, double y2, int depth);
void myLine(double x0, double y0, double x1, double y1);

int main() {

    G_init_graphics(800, 800);

    // Draw background
    G_rgb(0, 0, 0);
    G_clear();

    // Initial big triangle coordinates
    double x0 = 100, y0 = 100;
    double x1 = 700, y1 = 100;
    double x2 = 400, y2 = 700;

    G_rgb(0, 1, 0); // green lines

    triangle(x0, y0, x1, y1, x2, y2, 4); // trying depth 4

    G_wait_key();


    return 0;
}

void triangle(double x0, double y0, double x1, double y1, double x2, double y2, int depth) 
{
    // We are given the 3 points of the first triangle
    
    if (depth == 0) {
        // draw the triangle border
        myLine(x0, y0, x1, y1);
        myLine(x1, y1, x2, y2);
        myLine(x2, y2, x0, y0);
        return;
    }

    // Calculate midpoints
    double mx01 = (x0 + x1) / 2.0;
    double my01 = (y0 + y1) / 2.0;
    double mx12 = (x1 + x2) / 2.0;
    double my12 = (y1 + y2) / 2.0;
    double mx20 = (x2 + x0) / 2.0;
    double my20 = (y2 + y0) / 2.0;

    // Draw the line segments between them
    myLine(mx01, my01, mx12, my12);
    myLine(mx12, my12, mx20, my20);
    myLine(mx20, my20, mx01, my01);

    // Recurse into the 3 corner triangles
    triangle(x0, y0, mx01, my01, mx20, my20, depth - 1);
    triangle(mx01, my01, x1, y1, mx12, my12, depth - 1);
    triangle(mx20, my20, mx12, my12, x2, y2, depth - 1);
}

//using the parametric myLine copied from the file 'parametric_myLine.c'
void myLine(double x0, double y0, double x1, double y1) {
	for (double t = 0; t <= 1; t += 0.001) {   // small step = smoother line
		double x = x0 + t * (x1 - x0);
		double y = y0 + t * (y1 - y0);
		G_point(x, y);
    }

}
