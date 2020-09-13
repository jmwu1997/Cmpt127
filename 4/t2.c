#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "imgops.h"

void draw_rectangle( uint8_t array[], 
		     unsigned int cols, 
		     unsigned int rows, 
		     int x,
		     int y,
		     int rect_width,
		     int rect_height,
		     uint8_t color ){
int i,temp_x=1,temp_y=1;
if(rect_width!=0 && rect_height!=0){
	if(rect_width<0) temp_x=-1;
	if(rect_height<0) temp_y=-1;
	for(i=0;i<abs(rect_width);i++){
		if(0<=(x+i*temp_x) &&(x+i*temp_x)<cols) 
			if(y>=0 && y<rows) {
				set_pixel(array,cols,rows,i*temp_x+x,y,color);
				}
		if((x+i*temp_x)<cols) 
			if((y+rect_height)<rows) {
				set_pixel(array,cols,rows,i*temp_x+x,y+rect_height-temp_y,color);
				}
	}
	for(i=1;i<abs(rect_height);i++){
   		if(0<=x && x<cols) 
   			if((y+i*temp_y)>=0 && (y+i*temp_y)<rows) 
   				set_pixel(array,cols,rows,x,y+i*temp_y,color);
		if(0<=(x+rect_width) && (x+rect_width)<cols) 
			if((y+i*temp_y)>=0 && (y+i*temp_y)<rows)
				set_pixel(array,cols,rows,x+rect_width-temp_x,y+i*temp_y,color);
  	}
}

}
