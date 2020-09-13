#include <stdio.h>
int scrambled(int a[], int b[], int len){
  if(len==0) return 1;
  int i=0,j=0,temp=0,count=0;
  int c[len];
  for(i=0;i<len;i++) c[i]=1;
  i=0;
  while(i<len) {
    while(temp==0 && j<len){
      if(a[i]==b[j] && c[j]==1 ) {temp=1;count++;c[j]=0;}
      j++;
    }
    i++;
    if(count!=i) return 0;
    temp=0;
    j=0;
  }
  return 1;
}
