/*
 * imageops.c - Simple operations on images
 *
 * C laboratory exercises.
 * Richard Vaughan, 2014.
 */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*-------------------------------------------------
  PART 0: DEMONSTRATION 
*/


/* get the value in the array at coordinate (x,y)
 */
uint8_t get_pixel( const uint8_t array[], 
		   unsigned int cols, 
		   unsigned int rows,
		   unsigned int x,
		   unsigned int y )
{
  assert( x < cols );
  assert( y < rows );
  return array[ y*cols + x ];
}

/* set the pixel at coordinate {x,y} to the specified color
 */
void set_pixel( uint8_t array[], 
		unsigned int cols, 
		unsigned int rows,
		unsigned int x,
		unsigned int y,
		uint8_t color )
{
  assert( x < cols );
  assert( y < rows );
  array[ y * cols + x ] = color;
} 

/* Set every pixel to 0 (black) 
 */
void zero( uint8_t array[],
	   unsigned int cols,
	   unsigned int rows )
{
  // your code here.
  memset(array, 0, cols*rows*sizeof(uint8_t)); 
}

/*
  Returns a pointer to a freshly allocated array that contains the
  same values as the original array, or a null pointer if the
  allocation fails. The caller is responsible for freeing the array
  later.
*/
uint8_t* copy( const uint8_t array[], 
	       unsigned int cols, 
	       unsigned int rows )
{
  // your code here
  uint8_t* ret = malloc(cols*rows*sizeof(uint8_t));
  if (!ret) {
    perror("Call to malloc failed\n");
    exit(1);
  }
  memcpy(ret, array, cols*rows*sizeof(uint8_t));
  return ret;
}

/*-------------------------------------------------
  PART 1: OPERATIONS ON THE WHOLE IMAGE 
*/

/* TASK 1 - three easy functions to get started */


/* Return the darkest color that appears in the array; i.e. the
   smallest value
*/
uint8_t min( const uint8_t array[], 
         unsigned int cols, 
         unsigned int rows )
{
  int i,temp=*array;
  for(i=0;i<cols*rows*sizeof(uint8_t);i=i+sizeof(uint8_t)){
    if(temp>*(array+i)){
      temp=*(array+i);
    }
  }
  return temp;
}

/* Return the lightest color that appears in the array; i.e. the
   largest value
*/
uint8_t max( const uint8_t array[], 
         unsigned int cols, 
         unsigned int rows )
{
  unsigned int i;
  uint8_t temp=*array;
  for(i=0;i<cols*rows*sizeof(uint8_t);i=i+sizeof(uint8_t)){
    if(temp<*(array+i)){
      temp=*(array+i);
    }
  }
  return temp;
}

/* TASK 2 
   
   Replace every instance of pre_color with post_color.
*/
void replace_color(  uint8_t array[], 
		     unsigned int cols, 
		     unsigned int rows,
		     uint8_t pre_color,
		     uint8_t post_color )
{
  unsigned int i;
  for(i=0;i<cols*rows*sizeof(uint8_t);i=i+sizeof(uint8_t)){
    if(*(array+i)==pre_color){
      *(array+i)=post_color;
    }
  }
}

/* TASK 3  - two functions */

// flip the image, left-to-right, like in a mirror.
void flip_horizontal( uint8_t array[], 
		      unsigned int cols, 
		      unsigned int rows )
{  
  uint8_t * newarray=copy(array,cols,rows);
  unsigned int x=0,y=0;
  for(y=0;y<rows;y++){
    for(x=0;x<cols;x++){
      *(array+(x+y*cols)*sizeof(uint8_t))=*(newarray+(y*cols+cols-x)*sizeof(uint8_t));
    }
  }
  free(newarray); 
}

// flip the image top-to-bottom.
void flip_vertical( uint8_t array[], 
		    unsigned int cols, 
		    unsigned int rows )
{
  uint8_t * newarray=copy(array,cols,rows);
  unsigned int x=0,y=0;
  for(x=0;x<rows;x++){
    for(y=0;y<cols;y++){
      *(array+(x+y*cols)*sizeof(uint8_t))=*(newarray+(x+cols*(rows-y))*sizeof(uint8_t));
    }
  }
  free(newarray); 
}


/* TASK 4 
   
   Find the first coordinate of the first pixel with a value that
   equals color. Search from left-to-right, top-to-bottom. If it is
   found, store the coordinates in *x and *y and return 1. If it is
   not found, return 0.
*/
int locate_color(  const uint8_t array[], 
		   unsigned int cols, 
		   unsigned int rows,
		   uint8_t color,
		   unsigned int *x,
		   unsigned int *y )
{
  unsigned int i,j;
  for(i=0;i<rows;i++)
    for(j=0;j<cols;j++)
      if(get_pixel(array,cols,rows,j,i)==color) {*x=j;*y=i;return 1;}
  return 0;
}


/* TASK 5 
   
   Invert the image intensities, so that black becomes white and vice
   versa, and light shades of grey become the corresponding dark
   shade.
*/
void invert( uint8_t array[], 
	     unsigned int cols, 
	     unsigned int rows )
{
  unsigned int x,y;
  for(x=0;x<cols;x++){
    for(y=0;y<rows;y++){
      set_pixel(array,cols,rows,x,y,255-get_pixel(array,cols,rows,x,y));
    }
  }
}

/* TASK 6 
   
   Multiply every pixel by scale_factor, in order to brighten or
   darken the image.  Resulting values are rounded to the nearest
   integer (0.5 rounded up) and any value over 255 is thresholded to
   255.
*/
void scale_brightness( uint8_t array[],
		       unsigned int cols,
		       unsigned int rows,
		       double scale_factor )
{
  unsigned int x,y;
  for(x=0;x<cols;x++){
    for(y=0;y<rows;y++){
      set_pixel(array,cols,rows,x,y,round(scale_factor*get_pixel(array,cols,rows,x,y)));
      if(get_pixel(array,cols,rows,x,y)>255) set_pixel(array,cols,rows,x,y,255);
     }
  }
}


/* TASK 7 
   
   Normalize the dynamic range of the image, i.e. Shift and scale the
   pixel colors so that that darkest pixel is 0 and the lightest pixel
   is 255. 

   For example, if the darkest pixels in the original image had value
   10, all those pixels should have value 0 when the function
   returns. If the lightest pixels in the original image had value
   178, all those pixels should have value 255 when the function
   returns. All the pixels with intermediate values (i.e. [11 to 177])
   should be scaled proportionately.

   Hint: you already wrote min(), max() and scale_brightness().
*/
void normalize( uint8_t array[],
        unsigned int cols,
        unsigned int rows )
{
    uint8_t minium=min(array,cols,rows),maxium=max(array,cols,rows);
    double ratio;
    unsigned int x,y;
    ratio=(maxium-minium)/255;
    for(x=0;x<cols;x++){
      for(y=0;y<rows;y++){
        if(get_pixel(array,cols,rows,x,y)==minium) set_pixel(array,cols,rows,x,y,0);
        else if(get_pixel(array,cols,rows,x,y)==maxium) set_pixel(array,cols,rows,x,y,255);
        else scale_brightness(array,cols,rows,ratio);
      }
    }
}

/* TASK 8
   
   Return a new image of size rows/2 by cols/2. If the original image
   has an odd number of columns, ignore its rightmost column. If the
   original image has an odd number of rows, ignore its bottom row.
   The value of a pixel at (p,q) in the new image is the arithmentic
   mean of the 2x2 square of pixels starting from (2*p,2*q) in the
   original image.
*/
uint8_t* half( const uint8_t array[], 
           unsigned int cols, 
           unsigned int rows )
{
  if(cols%2!=0) cols--;
  if(rows%2!=0) rows--;
  unsigned int newcols=cols/2,newrows=rows/2,x,y;
  uint8_t* newarray=malloc(newcols*newrows*sizeof(uint8_t));
  if (!newarray) {
    perror("Call to malloc failed\n");
    exit(1);
  }
  for(y=0;y<newrows;y++){
    for(x=0;x<newcols;x++){
      set_pixel(newarray,newcols,newrows,x,y,(get_pixel(newarray,newcols,newrows,x*2-1,y*2-1)+get_pixel(newarray,newcols,newrows,x*2,y*2-1)+get_pixel(newarray,newcols,newrows,x*2+1,y*2-1)+get_pixel(newarray,newcols,newrows,x*2-1,y*2)+get_pixel(newarray,newcols,newrows,x*2,y*2)+get_pixel(newarray,newcols,newrows,x*2+1,y*2)+get_pixel(newarray,newcols,newrows,x*2-1,y*2+1)+get_pixel(newarray,newcols,newrows,x*2,y*2+1)+get_pixel(newarray,newcols,newrows,x*2+1,y*2+1))/9);
    }
  }
  return newarray;
}


/*-------------------------------------------------
  PART 2: OPERATIONS ON IMAGE SUB-REGIONS

  These functions operate only on a rectangular region of the array
  defined by a (left,top) corner (i.e. closer to the image origin) and
  (right,bottom) corner (i.e. further from the image origin).

  The region includes all the columns from [left, right-1] inclusive,
  and all the rows from [top, bottom-1] inclusive.
  
  In every case, you may assume that left <= right and top <= bottom:
  do not need to test for this.

  The area of the region is right-left * bottom-top pixels, which
  implies that if left == right or top == bottom, the region has no
  area and is defined as "empty". Each function notes how to handle
  empty regions.
*/

/* TASK 9 

   Set every pixel in the region to color. If the region is empty, the
   image must be unchanged.
*/
void region_set( uint8_t array[], 
		 unsigned int cols, 
		 unsigned int rows,
		 unsigned int left,
		 unsigned int top,
		 unsigned int right,
		 unsigned int bottom,
		 uint8_t color )
{
    unsigned int x,y;
  if(right!=left && bottom!=top)     
  for(y=0;y<(right-left);y++)
      for(x=0;x<(bottom-top);x++)
        set_pixel(array,cols,rows,x,y,color);
}

/* TASK 10 

   Return the sum of all the pixels in the region. Notice the large
   return type to handle potentially large numbers. Empty regions
   return the sum 0.
*/
unsigned long int region_integrate( const uint8_t array[], 
				    unsigned int cols, 
				    unsigned int rows,
				    unsigned int left,
				    unsigned int top,
				    unsigned int right,
				    unsigned int bottom )
{
  unsigned long int sum=0;
  unsigned int x,y;
  if(right==left || bottom==top) return 0;  
  for(y=0;y<(right-left);y++)
      for(x=0;x<(bottom-top);x++)
        sum=sum+get_pixel(array,cols,rows,x,y);
  return sum;
}

/* TASK 11 

   Get a new image which is a copy of the region. Empty regions return
   a null pointer. If memory allocation fails, return a null
   pointer. The caller is responsible for freeing the returned array.
*/
uint8_t* region_copy( const uint8_t array[], 
		      unsigned int cols, 
		      unsigned int rows,
		      unsigned int left,
		      unsigned int top,
		      unsigned int right,
		      unsigned int bottom )
{
  if(right==left || bottom==top) return NULL;
  unsigned int x,y;
  uint8_t* newarray=malloc((right-left)*(bottom-top)*sizeof(uint8_t));
  if (!newarray) {
    return NULL;
  }
  for(x=0;x<(right-left);x++)
    for(y=0;y<(bottom-top);y++)
      set_pixel(newarray,(right-left),(bottom-top),x,y,get_pixel(array,cols,rows,left+x,top+y));
  return newarray;
}

/* END */
