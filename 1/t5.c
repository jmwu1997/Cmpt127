#include <stdio.h>
#include <math.h>

int main(void){
  float i=0;
  while(scanf("%f",&i)!=EOF){
    printf("%g %g %g\n",floor(i),round(i),ceil(i));
    }
  printf("Done.\n");
  return 0;
}
