#include "FPToolkit.c"
#include<stdio.h>

// creating a function called myLine to replace the 
// G_line function


void myLine(double x0, double y0, double x1, double y1);

int main () {
/*
	//with G_line

	double p[2];

	G_wait_click(p);
	x[0] = p[0]; y[0] = p[1];
	G_rgb(1,0,0);
	G_fill_circle(x0, y0, 2); //mark first point

	G_wait_click(p);
	x1 = p[0]; y1 = p[1];
	G_rgb(0,0,1);
	G_fill_circle(x1,y1,2); //mark second point 

	//draw the line between them with G_line
	G_rgb(0,0,0);
	G_line(x0,y0,x1,y1);
*/
	//without G_line
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

void myLine(double x0, double y0, double x1, double y1) {
//point slope form is y-y0= m(x-x0)
//solving for y: y = y0+ m(x-x0)
	double slope = (y1 - y0) / (x1 - x0) ;
	for (double x = x0; x <= x1; x++) {
	    double y = y0 + slope * (x - x0) ;
	    G_point(x, y) ;
	}
}

