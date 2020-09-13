uint8_t get_pixel( const uint8_t array[], 
		   unsigned int cols, 
		   unsigned int rows,
		   unsigned int x,
		   unsigned int y );

void set_pixel( uint8_t array[], 
		unsigned int cols, 
		unsigned int rows,
		unsigned int x,
		unsigned int y,
		uint8_t color );

void zero( uint8_t array[],
	   unsigned int cols,
	   unsigned int rows );

uint8_t* copy( const uint8_t array[], 
	       unsigned int cols, 
	       unsigned int rows );

uint8_t min( const uint8_t array[], 
         unsigned int cols, 
         unsigned int rows );

uint8_t max( const uint8_t array[], 
         unsigned int cols, 
         unsigned int rows );

void replace_color(  uint8_t array[], 
		     unsigned int cols, 
		     unsigned int rows,
		     uint8_t pre_color,
		     uint8_t post_color );

void flip_horizontal( uint8_t array[], 
		      unsigned int cols, 
		      unsigned int rows );

void flip_vertical( uint8_t array[], 
		    unsigned int cols, 
		    unsigned int rows );

int locate_color(  const uint8_t array[], 
		   unsigned int cols, 
		   unsigned int rows,
		   uint8_t color,
		   unsigned int *x,
		   unsigned int *y );

void invert( uint8_t array[], 
	     unsigned int cols, 
	     unsigned int rows );


void scale_brightness( uint8_t array[],
		       unsigned int cols,
		       unsigned int rows,
		       double scale_factor );

void normalize( uint8_t array[],
        unsigned int cols,
        unsigned int rows );

uint8_t* half( const uint8_t array[], 
           unsigned int cols, 
           unsigned int rows );

void region_set( uint8_t array[], 
		 unsigned int cols, 
		 unsigned int rows,
		 unsigned int left,
		 unsigned int top,
		 unsigned int right,
		 unsigned int bottom,
		 uint8_t color );

unsigned long int region_integrate( const uint8_t array[], 
				    unsigned int cols, 
				    unsigned int rows,
				    unsigned int left,
				    unsigned int top,
				    unsigned int right,
				    unsigned int bottom );

uint8_t* region_copy( const uint8_t array[], 
		      unsigned int cols, 
		      unsigned int rows,
		      unsigned int left,
		      unsigned int top,
		      unsigned int right,
		      unsigned int bottom );




