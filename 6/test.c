#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "intarr.h"
#include "t2.h"

int main(void){
  	intarr_t* ia=intarr_create(10);
  	int i;
  	for(i=0;i<10;i++){
  		*(ia->data+i)=(int)13413123 % (i+1);
  	}
  	intarr_save_json(ia,"fuck me");
  	intarr_t* newia=intarr_load_json("fuck me");
  	for(i=0;i<newia->len;i++) printf("%d ",*(newia->data+i));
  	printf("\nlength=%u\n",newia->len);
  	free(newia);
  	free(ia);
	return 0;
}
