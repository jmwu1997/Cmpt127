#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "imgops.h"
int live(uint8_t array[],unsigned int cols,unsigned int rows,unsigned int x,unsigned int y){
  int counter=0;
  unsigned int tempx,tempy;
  if(x<1) tempx=cols+x-1; else tempx=x-1;
  if(y<1) tempy=rows+y-1; else tempy=y-1;
  if(get_pixel(array,cols,rows,tempx,tempy)>0) counter++;

  if(x<1) tempx=cols+x-1; else tempx=x-1;
  tempy=y;
  if(get_pixel(array,cols,rows,tempx,tempy)>0) counter++;

  if(x<1) tempx=cols+x-1; else tempx=x-1;
  if(y+1>=rows) tempy=y+1-rows; else tempy=y+1;
  if(get_pixel(array,cols,rows,tempx,tempy)>0) counter++;

  tempx=x;
  if(y<1) tempy=rows+y-1; else tempy=y-1;
  if(get_pixel(array,cols,rows,tempx,tempy)>0) counter++;

  tempx=x;
  if(y+1>=rows) tempy=y+1-rows; else tempy=y+1;
  if(get_pixel(array,cols,rows,tempx,tempy)>0) counter++;

  if(x+1>=cols) tempx=x+1-cols; else tempx=x+1;
  if(y<1) tempy=rows+y-1; else tempy=y-1;
  if(get_pixel(array,cols,rows,tempx,tempy)>0) counter++;

  if(x+1>=cols) tempx=x+1-cols; else tempx=x+1;
  tempy=y;
  if(get_pixel(array,cols,rows,tempx,tempy)>0) counter++;

  if(x+1>=cols) tempx=x+1-cols; else tempx=x+1;
  if(y+1>=rows) tempy=y+1-rows; else tempy=y+1;
  if(get_pixel(array,cols,rows,tempx,tempy)>0) counter++;
  
  return counter;
}

void life( uint8_t array[],unsigned int cols,unsigned int rows ){
  unsigned int x,y; 
  uint8_t * newarray=copy(array,cols,rows);
  for(y=0;y<rows;y++){
    for(x=0;x<cols;x++){
      if(get_pixel(array,cols,rows,x,y)>0){
        switch (live(array,cols,rows,x,y)){
          case 0:
          case 1: set_pixel(newarray,cols,rows,x,y,0);break;
          case 2: 
          case 3: break;
          case 4:
          case 5:
          case 6:
          case 7:
          case 8: set_pixel(newarray,cols,rows,x,y,0);break;
        }
      }
      if(get_pixel(array,cols,rows,x,y)==0)
      	if(live(array,cols,rows,x,y)==3)
      		set_pixel(newarray,cols,rows,x,y,255);
    }
  }
  for(y=0;y<rows;y++)
    for(x=0;x<cols;x++)
    	*(array+x+y*cols)=*(newarray+x+y*cols);
  free(newarray);
}
