// Nov 19, 2025

#include <stdio.h>
#include <math.h> 
#include <complex.h>
#include "FPToolkit.c"


int main()
{
    double x; 
    
    printf("Enter a guess for sqrt(5): ");
    scanf("%lf", &x);
  
    
    for (int i = 0; i <= 20; i++) {
        x = x - (x*x - 5.0) / (2.0 * x);  
        printf("Iteration %02d: %20.16lf\n", i + 1, x);
    }
    
    printf("Calculated sqrt(5) approx: %20.16lf\n", x);
    printf("Actual sqrt(5) value:      %20.16lf\n", sqrt(5.0));

    return 0;
}