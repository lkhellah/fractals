// L-System generating the Heighway Dragon Curve fractal.
#include "FPToolkit.c"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Constants for Graphics Window Size
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

// defines a Production rule
typedef struct Production 
{
    char var;
    char axiom[100];
    char rule [100];
} Production;


//Global variables;
Production prod[10]; 
char u[100000000]; 
char v[100000000]; 
double forward, single, angle; 


void string_builder();
void class_example();
int find_rule(char s);
void print_string(char array[]);
void string_interpreter();


int main ()
{
    // 1. Define L-system rules for the Dragon Curve
    class_example();
    
    // 2. Set drawing parameters (Turtle Graphics)
    // The Dragon Curve rules are standard: 90 degree turns.
    forward = 5.0;            // Smaller step needed for higher generations
    single = M_PI / 2.0;      // 90 degrees turn (M_PI/2)
    angle = 0.0;              // Start facing right (0 degrees)
    
    // 3. Build the fractal string
    string_builder();
   
    // 4. Interpret the string and draw the fractal
    string_interpreter();
    
    return 0;
}


void class_example () {
    // Defines the Heighway Dragon Curve L-system:
    
    // Axiom:
    strcpy(prod[0].axiom, "FX"); // Start with a single forward step (F) and the rotating variable (X)
    
    // Rule X (The main rotation rule): 
    // X generates the rightward (clockwise) turning section.
    prod[1].var = 'X';
    strcpy(prod[1].rule, "X+YF+");
    
    // Rule Y (The mirror rotation rule):
    // Y generates the leftward (counter-clockwise) turning section.
    prod[2].var = 'Y';
    strcpy(prod[2].rule, "-FX-Y");
}


void string_builder() {
    int c, depth, k, loc;
    char temp [2];
    
    // Dragon Curve requires higher depth for complexity.
    depth = 12; 
    
    u[0] = '\0';
    strcat(u, prod[0].axiom); 
    
    printf("--- L-System String Generation ---\n");
    print_string(u);

    for (c = 0; c < depth; c++) {
        k = 0;
        v[0] = '\0';
        
        while(u[k] != '\0') {
            loc = find_rule(u[k]);
            
            if (loc != -1) {
                strcat(v, prod[loc].rule);
            }
            else {
                // Copy non-rule symbols ('F', '+', '-') directly
                temp[0] = u[k];
                temp[1] = '\0';
                strcat(v, temp);
            }
            k++;
        }
        strcpy(u,v);
        print_string(u);
    }
    printf("--- String Generation Complete ---\n");
}


int find_rule(char s) {
    int k;
    for (k = 1; k <= 9; k++) {
        if (prod[k].var == '\0') break; 
        
        if (prod[k].var == s) {
            return k;
        }
    }
    return -1; 
}


void print_string(char array[]) {
    static int generation = 0;
    if (generation < 5) {
        printf("Generation %d (Length %lu): %s\n", generation, strlen(array), array);
    } else {
         printf("Generation %d (Length %lu)\n", generation, strlen(array));
    }
    generation++;
}


void string_interpreter() {
    // --- 1. Turtle State Initialization ---
    // Start position (x, y) - centered, slightly to the left
    double x = 350.0; 
    double y = 450.0;
    
    // Current direction (angle) - initialized to 0.0 (pointing right)
    double current_angle = angle; 

    // --- 2. Graphics Setup ---
    G_init_graphics(SCREEN_WIDTH, SCREEN_HEIGHT);
    G_rgb(0.95, 0.95, 1.0); 
    G_clear();
    G_rgb(0.1, 0.1, 0.1); // Black drawing color

    // --- 3. String Interpretation Loop ---
    int i = 0;
    while(u[i] != '\0') {
        char symbol = u[i];

        if (symbol == 'F') {
            // F: Move forward and draw a line
            double x_new, y_new;
            
            x_new = x + forward * cos(current_angle);
            y_new = y + forward * sin(current_angle);

            G_line(x, y, x_new, y_new);

            x = x_new;
            y = y_new;

        } else if (symbol == '+') {
            // +: Turn clockwise (right) by 90 degrees
            current_angle -= single;
        } else if (symbol == '-') {
            // -: Turn counter-clockwise (left) by 90 degrees
            current_angle += single;
        } 
        // X and Y are interpreted as *no operation* (NOP)
        
        i++;
    }
    
    G_wait_key();
}
