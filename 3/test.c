/*
 * test.cc - functions, arrays, pointers, image representation
 * Richard Vaughan 2014
 */

#include <stdlib.h> // for random()
#include <stdint.h> // for explicit integer types, eg. uint8_t
#include <string.h> // for memset()
#include <assert.h>
#include <stdio.h>

// include our own drawing functions
#include "draw.h"
#include "imgops.h"

// function to load PNG images, defined in "png.c"
int LoadPngImage(char *name, 
		 int *outWidth, 
		 int *outHeight, 
		 int *outDepth, 
		 int *outHasAlpha, 
		 uint8_t **outData);

// Generate a Siepinksi Carpet fractal:
// If the pixel at (x,y) in the Siepinksi Carpet fractal is set, returns 1, else 0
// See http://en.wikipedia.org/wiki/Sierpinski_carpet
int SierpinskiCarpetPixel(int x, int y)
{
  while(x>0 || y>0) 
    {
      if(x%3==1 && y%3==1) 
	return 0;
      x /= 3; 
      y /= 3;
    }
  return 1; 
}

void SierpinskiCarpet( uint8_t* img, int width, int height )
{
  // for each pixel in the image, if it set in the fractal, make it
  // white
  for( unsigned int x=0; x<width; x++ ) {
    for( unsigned int y=0; y<height; y++ ) {
      if( SierpinskiCarpetPixel( x, y ) )
	img[ x + y*width ] = 255;
    }
  }
} 

int main( int argc, char* argv[] )
{
  unsigned int winwidth  = 400;
  unsigned int winheight = 400; 

  if( argc >= 3)
    {
      winwidth  = atoi( argv[1] );
      winheight = atoi( argv[2] );
    }

  unsigned int imgwidth  = winwidth / 4;
  unsigned int imgheight = winheight / 4 ; 

  if( argc >= 5 )
    {
      imgwidth  = atoi( argv[3] );
      imgheight = atoi( argv[4] );
    }
    
  // initialize the graphics system
  draw_startup( (char*)"Grey Array", winwidth, winheight );
  
  if( argc == 2 )
    {
      uint8_t* photo = 0; 
      int w, h, depth, alpha;
      if( LoadPngImage( argv[1], &w, &h, &depth, &alpha, &photo ) == 0 )
	{
	  printf( "failed to load image %s\n", argv[1] );
	  exit(1);
	}
      
      imgwidth = w;
      imgheight = h;
      
      // draw the array as a grey-scale image in the window
      // This function returns after a user clicks or presses a button in the window
      draw_image_grey( photo, imgwidth, imgheight );
    }
  
  // allocate and zero an array for our image
  uint8_t* img = malloc( imgwidth * imgheight * sizeof(uint8_t) );
  memset( img, 0, imgwidth * imgheight * sizeof(img[0] ));

  // put some interesting values in the array
  SierpinskiCarpet( img, imgwidth, imgheight );

  // draw the array as a grey-scale image in the window
  // This function returns after a user clicks or presses a button in the window
  uint8_t* img1 = malloc( 4 * 3 * sizeof(uint8_t) );
  int z,count=1;
  for(z=0;z<12;z++){
    *(img1+z)=z;
    printf("%d  ",*(img1+z));
    if(count==4){ 
    	printf("\n");
    	count=0;
    	}
    count++;
    }
    
  printf("\n%lu\n",region_integrate(img1,4,3,0,0,4,3));
  count=1;
  for(z=0;z<12;z++){
	count+=*(img1+z);
    }
   printf("%d\n",count);
  // todo: zero and draw some more things here....

  
  
  // finalize the graphics system, freeing its resources
  draw_shutdown();

  // every malloc() should have a matching free()
  free(img);

  return 0;
}

