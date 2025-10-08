#include "FPToolkit.c"
#include<stdio.h>

void myLine(double x0, double y0, double x1, double y1);

// problem with G_line.c is that the original myLine
// assumes x1 > x0
// this code uses a parametric form 
// paramtetric form fixes the assumption because it doesn't care about slope
// now the second point can be behind the first (x2 < x1)

int main () {
        G_init_graphics(800, 800);   // open a window
        double p[2];
        double x0, y0, x1, y1;

        G_wait_click(p);
        x0 = p[0]; y0 = p[1];
        G_rgb(1,0,0);
        G_fill_circle(x0, y0, 2); //mark first point

        G_wait_click(p);
        x1 = p[0]; y1 = p[1];
        G_rgb(0,0,1);
        G_fill_circle(x1,y1,2); //mark second point


        //draw the line between them without G_line
        G_rgb(0,0,0);
        myLine(x0,y0,x1,y1);
        G_wait_key();

        return 0;
}

// draws line without G line
// make this function parametric
// want each point on the line to gradually change from a start color (sr, sg, sb) to 
// an end color (er, eg, eb) as t goes from 0 → 1.
void myLine(double x0, double y0, double x1, double y1) {
	for (double t = 0; t <= 1; t += 0.001) {   // small step = smoother line
		double x = x0 + t * (x1 - x0);
		double y = y0 + t * (y1 - y0);
		G_point(x, y);
    	}


}

