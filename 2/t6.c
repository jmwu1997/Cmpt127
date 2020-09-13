#include <stdio.h>
#include <string.h>

int main(void){
  int charcount=0,i=0,temp=0;
  float f[26];
  for(i=0;i<26;i++) f[i]=0;
  while((temp=getchar())!=EOF){
    for(i=0;i<26;i++)
    if((i+65)==temp || (i+97)==temp) {f[i]++;charcount++;break;}   
  }
  for(i=0;i<26;i++)
    if(f[i]>0) printf("%c %.4f\n",i+97,(f[i]/charcount));
  return 0;
}
