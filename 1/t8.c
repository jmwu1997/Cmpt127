#include <stdio.h>
#include <math.h>

int main(void)
{
  double x=0,y=0,z=0,i=0,j=0,k=0;
  scanf("%lf",&x);
  scanf("%lf",&y);
  scanf("%lf",&z);
  while(i<z)
  {
    if (i==(z-1)) 
    {
      for (k=0;k<x;k++) printf("#");
      printf("\n");
    }
    else 
    { 
      for (k=0;k<floor(x/2-x/(2*(z/(i+1))));k++) printf(" ");
      printf("#");
      for (k=floor(x/2-x/(2*(z/(i+1))))+1;k<(ceil(x/2+x/(2*z/(i+1))))-1;k++) 
      {
        if (i==0) printf("#"); else printf(".");
      }
      printf("#\n");
    }
    i++;
  }
  return 0;
}
