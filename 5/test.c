#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "intarr.h"

int main(void){
  int i;
  intarr_t* ia=intarr_create(4);
  intarr_set(ia,0,5);
  intarr_set(ia,1,2);
  intarr_set(ia,2,7);
  intarr_set(ia,3,31);
  intarr_resize(ia,2);
  for(i=0;i<ia->len;i++) printf("%d=:%d ",i,*(ia->data+i));
  printf("\n");
  intarr_destroy(ia);
  return 0;
}
