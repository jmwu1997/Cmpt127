#include <stdio.h>
#include <string.h>

int compare(char *a,char *b);

int main(int argc, char* argv[])
{
  int shit=0;
  shit=compare(argv[1],argv[2]);
  if(shit==1) printf("true\n");
  else printf("false\n");
  return 0;
}


int compare(char *a,char *b)
{
  int l1,l2,i=0,j=0,succeed=0;
  l1=strlen(a);
  l2=strlen(b);
  if(l2>l1) return 0;
  while(i<l1)
  {
    if(*b==*(a+i)) 
    {  
      succeed=1;
      for(j=0;j<l2;j++)
      {
        if(*(a+i+j)!=*(b+j)) succeed=0;
      }
      if(succeed==0) {i++;continue;}
      return 1;
    } 
    i++;
  }
  return 0;
}
