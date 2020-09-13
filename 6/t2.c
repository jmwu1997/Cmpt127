#include <stdio.h>
#include <stdlib.h>
#include "intarr.h"

/* LAB 6 TASK 2 */

/*
  Save the entire array ia into a file called 'filename' in a JSON
  text file array file format that can be loaded by
  intarr_load_json(). Returns zero on success, or a non-zero error
  code on failure. Arrays of length 0 should produce an output file
  containing an empty array.
  
  The JSON output should be human-readable.

  Examples:

  The following line is a valid JSON array:
  [ 100, 200, 300 ]
  
  The following lines are a valid JSON array:
  [ 
   100, 
   200, 
   300 
  ]
*/
int intarr_save_json( intarr_t* ia, const char* filename ){
	int i;		
	if(!ia) return 1;
	FILE* f = fopen(filename,"w");
	if(f == NULL){
		return 1;
	}
	if(fprintf(f,"[")<1) return 1;
	if(ia->len>0){
		for(i=0;i<(ia->len-1);i++){
			if(ia && ia->data+i){
				if(fprintf(f,"%d,\n",*(ia->data+i))<1){
					return 1;
				}
			}
		}
		if(fprintf(f,"%d",*(ia->data+ia->len-1))<1){
			fclose(f);
			return 1;
		}
	}
	if(fprintf(f,"]\n")<1){
		return 1;
	}
	fclose(f);
	return 0;
}


/*
  Load a new array from the file called 'filename', that was
  previously saved using intarr_save(). The file may contain an array
  of length 0. Returns a pointer to a newly-allocated intarr_t on
  success (even if that array has length 0), or NULL on failure.
*/
intarr_t* intarr_load_json( const char* filename ){
	int i=0;
	FILE* f=fopen(filename,"r");	
	if(f==NULL) return NULL;
	intarr_t* newia=intarr_create(1);
	if(!newia) return NULL;
	fgetc(f);
	while(fscanf(f,"%d,",(newia->data)+i)>=1) {
		if(intarr_resize(newia,i+2)!=INTARR_OK) return NULL;
		i++;
	}
	newia->len=i;
	fclose(f);
	return newia;
}
