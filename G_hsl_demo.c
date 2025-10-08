#include "FPToolkit.c"
   // needs version 105 or later


int main()
{

  G_init_graphics(800,800) ;

  G_rgb(0,0,0) ;
  G_clear() ;

  G_hsl(0,100,50) ;
  G_fill_circle(750,750,25) ;

  // color wheel 1
  double rad, t, l ;
  double x,y ;
  
  for(rad=200; rad>=1; rad--) {
    for(t=0;t<360;t+=0.1) {
      
      x = rad*cos(t*M_PI/180.0) + 250 ;
      y = rad*sin(t*M_PI/180.0) + 550 ;

      G_hsl(t,100,50) ;
      G_point(x,y) ;

    }
  }

 
  // color wheel 2
  for(rad=200; rad>=1; rad--) {
    for(t=0;t<360;t+=0.1) {
      
      x = rad*cos(t*M_PI/180.0) + 550 ;
      y = rad*sin(t*M_PI/180.0) + 250 ;

      G_hsl(t,rad/3.0,50) ;
      G_point(x,y) ;

    }
  }

  G_wait_key() ;


  for(l=100;l>=0;l--) {
    
    // color wheel 2 w/ change to lightness
    for(rad=200; rad>=1; rad--) {
      for(t=0;t<360;t+=0.1) {
	
	x = rad*cos(t*M_PI/180.0) + 250 ;
	y = rad*sin(t*M_PI/180.0) + 550 ;
	
	G_hsl(t,rad/3.0,l) ;
	G_point(x,y) ;
	
      }
    }
    
    
    // color wheel 2
    for(rad=200; rad>=1; rad--) {
      for(t=0;t<360;t+=0.1) {
	
	x = rad*cos(t*M_PI/180.0) + 550 ;
	y = rad*sin(t*M_PI/180.0) + 250 ;
	
	G_hsl(t,rad/3.0,50) ;
	G_point(x,y) ;
	
      }
    }
    
    G_wait_key() ;
    
    G_rgb(0,0,0) ;
    G_clear() ;
  }
  
}
