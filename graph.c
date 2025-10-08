#include "FPToolkit.c"

int main()
{
	int n ;

	// Ask user for input
	printf("Enter a positive integer (n): ") ;
	scanf("%d", &n) ;

	if (n <= 0) {
		printf("n must be positive!\n") ;
		return 1 ;
  	}

	
	// Make an 800x800 graphics window
	int size = 800 ;
	G_init_graphics(size, size) ;

	// Clear background to white
	G_rgb(1, 1, 1) ;
	G_clear() ;

	// Set line color to black
	G_rgb(0, 0, 0) ;

	// Compute gap size between lines
	double gap = (double)size / n ;

	// Draw vertical lines
	for (int i = 0; i <= n; i++) {
		double x = i * gap ;
		G_line(x, 0, x, size) ;
	}

	// Draw horizontal lines
	for (int j = 0; j <= n; j++) {
		double y = j * gap ;
		G_line(0, y, size, y) ;
	}

	// Wait for user to press a key
	G_wait_key() ;

	return 0 ;
}

