#include <stdio.h>
#include <string.h>
int compare_s(char a[],char b[],int num);
int main(int argc, char* argv[])
{
  int i=0,j=0 ,replace=0;
  char temp;
  char ca[128];
  while((temp=getchar())!=EOF)
  {
    ca[i]=temp;
    if(i==127 || temp<65 || (temp>90 && temp<97) || temp>122)
    {
      for(j=1;j<argc;j++){
      if(compare_s(ca,argv[j],i)==1) {printf("CENSORED%c",ca[i]);replace=1;i=-1;break;}
      } 
      if(replace==0) {for(j=0;j<=i;j++) printf("%c",ca[j]); i=-1;}
    }
    i++;
    replace=0;
  }
  return 0;
}


int compare_s(char* a,char b[],int num)
{
  int l1,l2,i=0,j=0,temp,succeed=0;
  l1=num;
  l2=strlen(b);
  if(l1!=l2) return 0;
  while(i<l1)
  {
    if(b[0]==*(a+i)) 
    {  
      temp=i;
      succeed=1;
      for(j=0;j<l2;j++)
      {
      if(*(a+temp+j)!=b[j]) return 0;
      }
      if(succeed==1) break;
    } 
    i++;
  }
  if(succeed) return 1; else return 0;

}
