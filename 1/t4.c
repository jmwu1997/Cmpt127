#include <stdio.h>
#include <math.h>

int main(void)
{
  float i=0,a=0;
  a=scanf("%f",&i);
  if(a==0){
    printf("scanf error: (%g)\n",a);
  }
  else{
    printf("%g %g %g\n",floor(i),round(i),ceil(i));
  }  
return 0;
}
