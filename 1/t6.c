#include <stdio.h>
#include <math.h>

int main(void)
{
  float i=0, smallest=0, largest=0,sum=0,n=0;
  if (scanf("%f",&i)!=EOF)
  {
    smallest=i;
    largest=i;
    sum=sum+i;
    n++;
  }
  while (scanf("%f",&i)!=EOF)
  {
    if(smallest>i) smallest=i;
    if(largest<i) largest=i;
    sum=sum+i;
    n++;
  }
  printf("%.2f %.2f %.2f\n",smallest,largest,sum/n);
  return 0;
}

