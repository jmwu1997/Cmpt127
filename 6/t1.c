#include <stdio.h>
#include <stdlib.h>
#include "intarr.h"

int intarr_save_binary( intarr_t* ia, const char* filename ){
	FILE* f = fopen(filename,"w");
	if(!ia) return 1;
	if(f == NULL){
		return 1;
	}
	if(fwrite(&(ia->len),sizeof(unsigned int),1,f)!=1){
		return 1;
	}
	if(fwrite(ia->data,sizeof(int),ia->len,f)!=ia->len){
		return 1;
	}
	fclose(f);
	return 0;
}

intarr_t* intarr_load_binary( const char* filename ){
	intarr_t* newia=malloc(sizeof(intarr_t));
	if(!newia) return NULL;
	FILE* f=fopen(filename,"r");
	if(f == NULL){
		return NULL;
	}
	if(fread(&(newia->len),sizeof(unsigned int),1,f)!=1){
		return NULL;
	}
	newia->data = malloc(sizeof(int)*newia->len);
	if(!newia->data) return NULL;
	if(fread(newia->data,sizeof(int),newia->len,f)!=newia->len){
		return NULL;
	}
	fclose(f);
	return newia;
}




