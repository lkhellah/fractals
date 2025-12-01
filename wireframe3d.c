//Dec 1 2025

#include <stdio.h>
#include <math.h> 
#include <complex.h>
#include <stdlib.h> 
#include "FPToolkit.c"

double xplot[1000];
double yplot[1000];
double x[100000], y[100000], z[100000];
int N;

void build_pyramid();
void draw();
void rotate_x(double degrees);
void rotate_y(double degrees);
void rotate_z(double degrees);
void translate(double dx, double dy, double dz);
void save_line(double x0,double y0,double z0, double x1,double y1,double z1);



int main()
{
    G_init_graphics(800,800);
    G_rgb(0,0,0);
    G_clear();

    build_pyramid();  // Build the 3D model

    // Move pyramid slightly forward so projection is visible
    translate(0,0,3);  

    // Animation loop
    while (1) {
        G_rgb(0,0,0);  // clear screen
        G_clear();

        rotate_y(1);   // spin the pyramid
        rotate_x(0.5); // slow tilt

        draw();        // draw wireframe

        G_wait_key();
    }

    return 0;
}

void build_pyramid()
{
    N = 0;
    //save_line(-1, -1, -1, -1, -1, 1);
    //save_line(-1, -1, 1, 1, -1, 1);
    //...

    // Base square (side = 2)
    save_line(-1, -1, 0,   1, -1, 0);
    save_line( 1, -1, 0,   1,  1, 0);
    save_line( 1,  1, 0,  -1,  1, 0);
    save_line(-1,  1, 0,  -1, -1, 0);

    // Apex at (0,0,1.5)
    double ax = 0, ay = 0, az = 1.5;

    // 4 side triangles
    save_line(ax,ay,az,   -1,-1,0);
    save_line(ax,ay,az,    1,-1,0);
    save_line(ax,ay,az,    1, 1,0);
    save_line(ax,ay,az,   -1, 1,0);
}


void translate(double dx, double dy, double dz) {
    int i; 
    for(i= 0; i<N; i++) {
        x[i] = x[i] + dx;
        y[i] = y[i] + dy;
        z[i] = z[i] + dz;
    }
}

void rotate_x(double degrees){
    int i; 
    double temp;
    double r = degrees * M_PI/180;
    double co = cos(r);
    double si = sin(r);
    for (i=0; i<N; i++) {
        temp = co * y[i] - si*z[i];
        z[i] = si*y[i] + co*z[i];
        y[i] = temp;
    }
}

void rotate_y(double degrees){
    int i; 
    double temp;
    double r = degrees * M_PI/180;
    double co = cos(r);
    double si = sin(r);
    for (i=0; i<N; i++) {
        temp = co * x[i] + si*z[i];
        z[i] = -si*x[i] + co*z[i];
        x[i] = temp;
    }
}

void rotate_z(double degrees){
    int i; 
    double temp;
    double r = degrees * M_PI/180;
    double co = cos(r);
    double si = sin(r);
    for (i=0; i<N; i++) {
        temp = co * x[i] - si*y[i];
        y[i] = si*x[i] + co*y[i];
        x[i] = temp;
    }
}

void save_line(double x0,double y0,double z0,
               double x1,double y1,double z1)
{
    x[N] = x0; y[N] = y0; z[N] = z0;  N++;
    x[N] = x1; y[N] = y1; z[N] = z1;  N++;
}


void draw()
{
    int i;

    G_rgb(1,1,1);

    for (i = 0; i < N; i += 2) {

        if (z[i] < 0.1 || z[i+1] < 0.1) continue; 
        // Simple perspective projection
        double px0 = x[i]   / z[i];
        double py0 = y[i]   / z[i];
        double px1 = x[i+1] / z[i+1];
        double py1 = y[i+1] / z[i+1];

        // Convert to screen coordinates
        px0 = px0 * 200 + 400;
        py0 = py0 * 200 + 400;
        px1 = px1 * 200 + 400;
        py1 = py1 * 200 + 400;

        G_line(px0, py0, px1, py1);
    }
}

/*
y'/H = yp-400/40
400/h *y' + 400 = yp+xp  // which is G_line
*/