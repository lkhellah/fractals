// L-system example
/*This file implements the Square Koch Curve using the L-System principles. 
This fractal replaces every line segment with a small square wave pattern, 
generating a complex, self-similar boundary.*/

// L-system example: Generates the Square Koch Curve (a square wave fractal)
#include "FPToolkit.c"
#include <math.h>
#include <string.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Constants for L-System
#define MAX_STRING_LENGTH 20000000 
#define MAX_DEPTH 5 // Depth remains 5

// Global L-System string buffers
char u[MAX_STRING_LENGTH]; // Current generation string
char v[MAX_STRING_LENGTH]; // Next generation string buffer


// The grammar for the Square Koch Curve
// Axiom: A single forward segment 'F'
// Rule: F -> F+F-F-F+F
// Angle: 90 degrees (pi/2)

// --- FUNCTION PROTOTYPES ---
void string_builder(int depth);
void string_interpreter(double start_x, double start_y, double initial_length);

// --- MAIN FUNCTION ---
int main () {

    // 1. Build the fractal string
    string_builder(MAX_DEPTH);
    
    // 2. Interpret the string and draw
    
    // Initial length of the entire curve (L0) - set to fill the 800x800 screen well.
    double initial_length = 600.0; 
    
    // Starting position and angle adjustment: 
    // Start at (100, 400) and point right (0.0 radians) 
    // to draw the fractal horizontally across the center of the screen.
    double start_x = 100.0;
    double start_y = 400.0;

    string_interpreter(start_x, start_y, initial_length);
    
    return 0;
}

// --- L-SYSTEM STRING BUILDER ---
void string_builder(int depth) {
    int c, k;
    char temp [2];
    
    // AXIOM: The starting string for the Square Koch Curve
    strcpy(u, "F"); 
    printf("--- L-System String Generation (Square Koch) ---\n");
    printf("Generation 0: %s\n", u);

    for (c = 0; c < depth; c++) {
        k = 0;
        v[0] = '\0'; // Clear the next generation buffer
        
        while(u[k] != '\0') {
            char current_symbol = u[k];
            
            if (current_symbol == 'F') {
                // RULE: F -> F+F-F-F+F
                strcat(v, "F+F-F-F+F");
            }
            else {
                // Symbols like '+', '-', 'X', 'Y', etc., are copied directly (identity rule)
                temp[0] = current_symbol;
                temp[1] = '\0';
                strcat(v, temp);
            }
            k++;
        }
        
        // Copy the new string (v) back to the current string (u) for the next iteration
        strcpy(u,v);
        printf("Generation %d (Length %lu)\n", c + 1, strlen(u));
        
        // Safety check to prevent crashing if the string gets too long
        if (strlen(u) >= MAX_STRING_LENGTH - 100) {
            printf("Warning: Max string length reached. Stopping recursion.\n");
            break;
        }
    }
    printf("--- String Generation Complete ---\n");
}


// --- TURTLE GRAPHICS INTERPRETER ---
void string_interpreter(double start_x, double start_y, double initial_length) {
    
    // CALCULATE SCALED STEP DISTANCE:
    // The Square Koch Rule replaces 1 segment with 5 segments, but the fractal 
    // is self-similar with a ratio of 1/3 (the step distance must shrink by 1/3 each time).
    // forward_step = initial_length * (1/3)^MAX_DEPTH
    double forward_step = initial_length / pow(3.0, MAX_DEPTH);
    
    // --- Turtle State Initialization ---
    double x = start_x; 
    double y = start_y;
    double angle = 0.0; // Start pointing RIGHT (0 radians), changed from UP (pi/2)
    double turn_angle = M_PI / 2.0; // 90 degrees turn for the Square Koch Curve

    // --- Graphics Setup ---
    G_init_graphics(800, 800);
    G_rgb(0.95, 0.95, 0.95); // Light background
    G_clear();
    G_rgb(0.1, 0.1, 0.5); // Dark blue drawing color

    // --- String Interpretation Loop ---
    int i = 0;
    while(u[i] != '\0') {
        char symbol = u[i];

        if (symbol == 'F') {
            // F: Move forward and draw a line
            double x_new, y_new;
            
            x_new = x + forward_step * cos(angle);
            y_new = y + forward_step * sin(angle);

            G_line(x, y, x_new, y_new);

            x = x_new;
            y = y_new;

        } else if (symbol == '+') {
            // +: Turn clockwise (right) by 90 degrees
            angle -= turn_angle;
        } else if (symbol == '-') {
            // -: Turn counter-clockwise (left) by 90 degrees
            angle += turn_angle;
        } 
        // Other symbols (if any) are ignored for drawing
        
        i++;
    }
    
    G_wait_key();
}
