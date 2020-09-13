#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "list.h"

void list_half(list_t* list,list_t* list_a,list_t* list_b){
		if(list->head->next == NULL)
			list
}
	
list_t* list_merge(list_t* list_a,list_t* list_b);

void list_sort(list_t * list){
	list_t* list_a=list_create();
	list_t* list_b=list_create();
	if(list->head->next == NULL || list->head == NULL) 
		return;
	list_half(list,list_a,list_b);
	list_sort(list_a);
	list_sort(list_b);
	list=list_merge(list_a,list_b);
}
