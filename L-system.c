/*
Lindenmayer system (L-system)
generating fractals using string rewriting rules 
instead of geometry or recursion directly.
*/


// defines a Production rule — it holds:
// var → the variable or symbol (like F or X)
// axiom → the starting string
// rule → what that variable turns into (its rewrite rule)
typedef struct Production 
{
char var;
char axiom[100];
char rule [100];


} Production;



//Global variables;
Production prod[10]; // stores up to 10 production rules.
char u[100000000]; // long string that will hold the result after several iterations of applying the rules. 
// the turtle moves off of u
char v[100000000]; // temp to write the new string into temporarily 
double forward, single, angle;


void string_builder();
void class_example();
int find_rule(char s);
void print_string(char array[]);
void string_interpreter();

int main ()
{
    // call class example to define rules
    // class_example()
    
    // then call string builder
    // string_builder()
   
    // read u one at a time and interpret
    // string_interpreter()
    return 0;
}

void class_example () {
    // defining the L-systen 
    // This function sets the L-system as: 
    // Axiom = "FV"
    // F → FV+
    // V → F+

    prod[0].axiom;
    strcpy(prod[0].axiom, "FV"); //sets the starting axiom - the seed string for our fractal system
    
    //defining rule for F: 
    // whenever you see an F in the current string, replace it with "FV+" in the next generation.
    prod[1].var = 'F';
    strcpy(prod[1].rule, "FV+");
    
    //defining rule for V
    // Replace V with "F+" every time it appears.
    prod[2].var = 'V';
    strcpy(prod[2].rule, "F+");
}


void string_builder() {
    int c, depth, k, loc;
    char temp [2];
    u[0] = '\0';
    strcat(u, prod[0].axiom); // u is what we concatenate to, prod[0].axiom is what we are adding
    print_string(u);
    // if u = "FV", using the production rules, we want the result to be "F V + F + \0" (array size 6)
    depth = 3;
    for (c = 0; c < depth; c++) {
        k = 0;
        v[0] = '\0';
        while(u[k] != '\0') {
            loc = find_rule(u[k]);
            if (loc != -1) {
                strcat(v, prod[loc].rule);
            }
            else {
                temp[0] = u[k];
                temp[1] = '\0';
                strcat(v, temp);
            }
        }
        strcpy(u,v);
        print_string(u);
    }
}

int find_rule(char s) {

    int k;
    for (k = 1; k <= 9; k++) {
        if (prod[k].var == s) {
            return k;
        }
    }
    return -1;
}

void print_string(char array[]) {
    static int generation = 0;
    printf("Generation %d: %s\n", generation, array);
    generation++;
    return 0;
}


void string_interpreter() {
    // G_line
}