# Makefile for RASTER lab by RTV. 

# Makefiles help manage the compilation process.  To use this
# Makefile, run 'make' in the directory containing this file.

# source files
SRC = test.c imgops.c draw.c png.c

# compiler options
CFLAGS = -std=c99 -g -Wall

# $ make
# - default target
# - works in CSIL and probably most Linux distros.
img: $(SRC) draw.h
	gcc $(CFLAGS) `pkg-config --cflags x11` -o img $(SRC) `pkg-config --libs x11` -lm -lpng

# $ make manual
#  - try this target if the first one doesn't work for you. 
#  - this one works on OS X with XQuartz installed.
manual: $(SRC) draw.h
	gcc $(CFLAGS) -I/usr/X11R6/include -o img $(SRC) -L/usr/X11/lib -lX11 -lm -lpng

# $ make clean
#  - removes files we built using the targets above
clean:
	rm -f img *.o
