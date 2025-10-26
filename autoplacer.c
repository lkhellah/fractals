double x,y;

void scale (sfx, sfy) {

	x = sfx * x;
	y = sfy * y;

}

void translate (cx, cy) {
    // x = ... 
   //  y  = ...
}


int main( ) {

    int cx, cy, sfx, sfy, angle;

    //rotate
    translate (cx, cy);
    rotate (angle);
    translate (cx,cy);
    
    //scale 
    translate(cx, cy);
    scale (sfx, sfy);
    translate (cx, cy);

}
