//IFS fractal code (Iterated Function System
// making the Sierpinski Carpet

#include "FPToolkit.c"
#include <math.h>



double x[13] = {0};
double y[13] = {0};
int n = 1;

// These build a diagonal line
/*
Rule 1
B1: Scale(0.5 , 0.5)
    
Rule 2
B2:
    Scale(0.5 , 0.5)
    Translate(0.5 , 0.5)
*/

//These build the sierpinski carpet
/*
B1: scale(0.5, 0.5);
B2: scale(0.5, 0.5);
    translate(0.5, 0);
B3: scale(0.5, 0.5);
    translate(0, 0.5);
B4: scale(0.5, 0.5);
    rotate(180); 
    translate(0.5, 0.5);
*/

//sierpinski carpet part 2
/*
B1: scale(0.5, 0.5);
B2: scale(0.5, 0.5);
    translate(0.5, 0);
B3: scale(0.5, 0.5);
    translate(0, 0.5);
*/

// 2 triangles: 1  black 1 white 
/*
B1: scale(sqrt(2)/2, sqrt(2)/2);
    rotate(-135);
    translate(0.5, 0.5);

B2: scale(sqrt(2)/2, sqrt(2)/2);
    rotate(135);
    translate(0.5, 0.5);
*/
void translate(double dx, double dy);
void scale (double sx, double sy);
void rotate (double degrees);



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
                 scale(0.5, 0.5);
               
            }
            else if (r < 0.5){
                //B2
                scale(0.5, 0.5);
                translate(0.5, 0);
            }
            else if (r < 0.75){
                //B3
                scale(0.5, 0.5);
                translate(0, 0.5);
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