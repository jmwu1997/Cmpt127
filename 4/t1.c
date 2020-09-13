#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include "imgops.h"



void draw_circle(uint8_t img[],unsigned int cols,unsigned int rows,int x,int y,int r,uint8_t color){
  int i,j;
  float temp1,temp2,tempr=r;
  for(i=0;i<rows;i++){
    for(j=0;j<cols;j++){
      if(i-y<0){
        temp1=i+0.5;
        if(j-x<0) temp2=j+0.5;
        else if (j-x>0) temp2=j-0.5;
        else temp2=j;
      }
      if(i-y>0){
        temp1=i-0.5;
        if(j-x<0) temp2=j+0.5;
        else if (j-x>0) temp2=j-0.5;
        else temp2=j;
      }
      if(i-y==0){
        temp1=i;
        if(j-x<0) temp2=j+0.5;
        else if (j-x>0) temp2=j-0.5;
        else temp2=j;
      }
      if(tempr!=0)
      if((((temp1-y)*(temp1-y))+((temp2-x)*(temp2-x)))<(tempr*tempr)){
        set_pixel(img,cols,rows,j,i,color);
        }
    }
  }
}
