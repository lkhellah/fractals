// IFS fractal code (Iterated Function System
// making Koch curve —> specifically the Koch snowflake edge

#include "FPToolkit.c"
#include <math.h>

double x[13] = {0};
double y[13] = {0};
int n = 1;


void translate(double dx, double dy);
void scale (double sx, double sy);
void rotate (double degrees);

/*
Rules

B1: scale(1.0/3.0, 1.0/3.0);
B2: scale(1.0/3.0, 1.0/3.0);
    translate(2.0/3.0, 0);
B3: scale(1.0/3.0, 1.0/3.0);
    rotate(60);
    translate(1.0/3.0, 0);
B4: scale(1.0/3.0, 1.0/3.0);
    rotate(-60);
    translate(0.5, sqrt(3)/6);
*/

int main() {

    double r;
    G_init_graphics(800,800);
    G_rgb(0,0,0);
    G_clear();
    G_rgb(1,1,1);

    for (int i=0; i < 2000000; i++) {
            r = drand48();
            if(r < 0.25) {
                //B1
                 scale(1.0/3.0, 1.0/3.0);
            }
            else if (r < 0.5){
                //B2
                scale(1.0/3.0, 1.0/3.0);
                translate(2.0/3.0, 0);
            }
            else if (r < 0.75){
                //B3
                scale(1.0/3.0, 1.0/3.0);
                rotate(60);
                translate(1.0/3.0, 0);
            }
            else {
                scale(1.0/3.0, 1.0/3.0);
                rotate(-60);
                translate(0.5, sqrt(3)/6);
            }
        G_point(x[0]*800, y[0]*800);
    }


    G_wait_key();


    return 0;
}



void translate(double dx, double dy) {
    int i; 
    for(i = 0; i < n; i++) {
        x[i] += dx;
        y[i] += dy;
    }
}


void scale (double sx, double sy) {
    int i;
    for(i = 0; i < n; i++) {
        x[i] *= sx;
        y[i] *= sy;
    }
}

void rotate (double degrees) {
    double radians = degrees *M_PI/180;
    int i;
    double temp;
    double c = cos(radians);
    double s = sin(radians);
    for(i = 0; i < n; i++) {
        temp = x[i]*c - y[i]*s;
        y[i] = x[i]*s + y[i]*c;
        x[i] = temp;

    }
}