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
#include "t3.h"

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
  unsigned int winwidth  = 50;
  unsigned int winheight = 50; 

  if( argc >= 3)
    {
      winwidth  = atoi( argv[1] );
      winheight = atoi( argv[2] );
    }

  unsigned int imgwidth  = 10;
  unsigned int imgheight = 10 ; 

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
      
      imgwidth = 193;
      imgheight =96;
      
      // draw the array as a grey-scale image in the window
      // This function returns after a user clicks or presses a button in the window
      draw_image_grey( photo, imgwidth, imgheight );
    }
  
  // allocate and zero an array for our image
  uint8_t* img = malloc( imgwidth * imgheight * sizeof(uint8_t) );
  memset( img, 0, imgwidth * imgheight * sizeof(img[0] ));

  // put some interesting values in the array
  //SierpinskiCarpet( img, imgwidth, imgheight );

  // draw the array as a grey-scale image in the window
  // This function returns after a user clicks or presses a button in the window
 int glider[][2] = { {1,0}, {2,1}, {0,2}, {1,2}, {2,2} };   

  for( int i=0; i<5; i++ )
    set_pixel( img, imgwidth, imgheight, glider[i][0], glider[i][1], 255 );
  
  for( int i=0; i<64; i++ )
    { 
      draw_image_grey( img, imgwidth, imgheight );
      life( img, imgwidth, imgheight );
    } 
  draw_image_grey( img, imgwidth, imgheight );

 
  // todo: zero and draw some more things here....
  
  
  // finalize the graphics system, freeing its resources
  draw_shutdown();

  // every malloc() should have a matching free()
  free(img);

  return 0;
}









