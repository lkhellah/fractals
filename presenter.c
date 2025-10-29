#include "FPToolkit.c"

void translate(double dx, double dy);
void scale (double sx, double sy);
void rotate (double degrees);

double x[13] = {175, 225, 225, 300, 225, 225, 250, 200, 150, 175, 175, 100, 175};
double y[13] = {300, 300, 250, 225, 225, 200, 100, 175, 100, 200, 225, 225, 250};
int n = 13;


int main() {
    G_init_graphics(400,400);
    G_rgb(0,0,0); G_clear();
    G_rgb(0,1,0); G_fill_polygon(x,y,n);

    for (int i = 0; i < 4; i++) {
       // translate(100,50);
       // scale(0.5, 0.5);
        rotate(30);
    }


    G_rgb(0,0,1); G_fill_polygon(x,y,n);

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


