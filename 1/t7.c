#include <stdio.h>
#include <math.h>

int main(void)
{
  int x,y,z,i,j,k=0;
  scanf("%d",&x);
  scanf("%d",&y);
  scanf("%d",&z);
  while(i<=(y-1))
  {
    if (i==0 || i==(y-1)) 
    {
      for (k=0;k<x;k++) printf("#");
      printf("\n");
    }
    else
    {
      printf("#");
      for (k=1;k<(x-1);k++) printf(".");
      printf("#\n");
    }
    i++;
  }
  return 0;
}
