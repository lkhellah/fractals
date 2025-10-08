#include "FPToolkit.c"
  // needs version 105 or later

int main()
{
  int n ;
  double x[100],y[100] ;
  
  G_init_graphics(800,600) ;

  // override default lower left button coords of (0,0) ;
  G_click_and_save_button_lower_left_x = 700 ;
  G_click_and_save_button_lower_left_y = 500 ;
  // other features can also be overridden, see FPToolkit code for
  // relevant variables
  
  n = G_click_and_save(x,y) ;

  G_rgb(1,1,1) ;
  G_clear() ;
  
  G_rgb(1,0,0) ;
  G_fill_polygon(x,y,n) ;
  
  G_wait_key() ;
}
