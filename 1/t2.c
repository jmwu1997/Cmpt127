#include <stdio.h>

int main(void)
{
  printf("%lu %lu %lu %lu %lu %lu %lu %lu %lu\n", sizeof(char)*8,sizeof(unsigned char)*8,sizeof(int)*8,sizeof(unsigned int)*8,sizeof(long)*8,sizeof(unsigned long)*8,sizeof(float)*8,sizeof(double)*8,sizeof(long double)*8);
  return 0;
}
