#include <stdio.h>

int main(void)
{
  int temp,wordend=0,wordstart=0;
  unsigned long charcount=0,wordcount=0,linecount=0,previous=0;
  if((temp=getchar())==EOF) {printf("0 0 0\n");return 0;}
  else {   
      charcount++;
      if((temp>64&&temp<91) || (temp>96&&temp<123) || temp==39) {wordstart=1;}
      else if(temp==10) {linecount++;if(wordstart==1){wordcount++;wordstart=0;}}
      else if(wordstart==1) {wordcount++;wordstart=0;}
      previous=temp;
  }
  while((temp=getchar())!=EOF)
  {   
      charcount++;
      if((temp>64&&temp<91) || (temp>96&&temp<123) || temp==39) {wordstart=1;}
      else if(temp==10) {linecount++;if(wordstart==1){wordcount++;wordstart=0;}}
      else if(wordstart==1) {wordcount++;wordstart=0;}
      previous=temp;
  }
  if(temp==EOF && (previous>64&&previous<91) || (previous>96&&previous<123) || previous==39)  {
    wordcount++;linecount++;
  }
  printf("%lu %lu %lu\n",charcount,wordcount,linecount);
  return 0;
}
