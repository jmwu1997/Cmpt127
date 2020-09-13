#include <stdio.h>

int main(void){
	int a=0;
	FILE* f=fopen("mine","r");
	while(fscanf(f,"%d",&a)>=1) printf("%d\n",a);
	printf("\n");
	fclose(f);
return 0;
}
