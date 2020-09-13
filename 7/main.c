#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include "list.h"
#include <assert.h>
#include <string.h>

int test_element_create( void );

int main(void )
{
  if(test_element_create() ==1) return 1;
  srand(time(NULL));
  int temp=rand()%50;
  int buff1=temp;
  list_t* list;
//test create list
  for(int i=0;i<10;i++){
  	list = list_create();
  	if(!list || list->head || list->tail ){
  		printf("list create failed\n");
  		return 1;
  	}
  	list->head=malloc(1);
  	list->tail=malloc(1);
  	free(list->head);
  	free(list->tail);
  	free(list);
  }
  list=list_create();
  
//test appending one element to a null list
  if(list_append(list,temp)!=0){
  	printf("list append failed\n");
  	return 1;
  }
  if(list->head->val !=temp || list->tail->val != temp ||  list->tail->next !=NULL || list->head->next != NULL || list->head != list->tail){
  	printf("wrong append\n");
  	return 1;
  }
  
  
  printf("one element list sucessfully created.\n");
//test append one element to a one-element list
  element_t* el1=list->tail;
  
  temp=rand()%30;
 //int buff2=temp;
  
  if(list_append(list,temp)!=0){
  	printf("list append failed of non-null list\n");
  	return 1;
  }
  
  if(el1->next!=list->tail || list->tail->val!=temp || list->tail->next!=NULL){
  	printf("failed trying to append another val\n");
  	return 1;
  }
  
  if(list->head->val != buff1 || list->head->next != list->tail){
  	printf("head wrong\n");
  	return 1;
  }

  printf("append sucessfully for size 2\n");
  
//test appending one more element o a size 2 list
  temp=rand()%55;
  //int buff3=temp;
  el1=list->tail;
  element_t* el2=malloc(sizeof(element_t));
  el2->val=list->head->val;
  el2->next=list->head->next;
  if(list_append(list,temp)!=0){
  	printf("list append failed of non-null list\n");
  	return 1;
  }
  if(el1->next!=list->tail || list->tail->val!=temp || list->tail->next!=NULL){
  	printf("failed trying to append another val\n");
  	return 1;
  }
  if(el2->val != list->head->val || el2->next != list->head->next){
  	printf("head wrong\n");
  	return 1;
  }
  printf("append works fine\n");
  
  

  
  list_destroy( list );
  
//test prepend
  temp=rand()%53;
  int buff4=temp;
  list = list_create();
  if(list_prepend(list,temp)!=0){
  	printf("list prepend failed\n");
  	return 1;
  }
  
  if(list->head->val !=temp || list->tail->val != temp ||  list->tail->next !=NULL || list->head->next != NULL || list->head != list->tail){
  	printf("wrong prepend\n");
  	return 1;
  }
  printf("prepend one element sucessfully");
  list_print(list);
  
//test prepend one element to a one-element list
  el1=list->head;
  
  temp=rand()%37;
  //int buff5=temp;
  
  if(list_prepend(list,temp)!=0){
  	printf("list append failed of non-null list\n");
  	return 1;
  }
  
  if(el1!=list->head->next || list->head->val!=temp || list->tail->next!=NULL){
  	printf("failed trying to prepend another val\n");
  	return 1;
  }
  
  if(list->tail->val != buff4){
  	printf("tail wrong\n");
  	return 1;
  }

  printf("prepend sucessfully for size 2\n");
  list_print(list);
  
//test prepend one element to a list of size 2
  temp=rand()%59;
  el1=list->head;
  //int buff6=temp;
  if(list_prepend(list,temp)!=0){
  	printf("list prepend failed of non-null list\n");
  	return 1;
  }
  if(el1!=list->head->next || list->head->val!=temp || list->tail->next!=NULL){
  	printf("list prepend failed");
  	return 1;
  }
  if(list->tail->val!=buff4){
  	printf("tail wrong\n");
  	return 1;
  }
  printf("prepend passed");
  list_print(list);
  
  
  
  
  
  
  
  
  list_destroy(list);
  list=list_create();
  list_print(list);
   //int a[]={0,0,0,0,0};
    for( int i=0; i<5; i++ ){
    	temp=(int)(rand()%(i*20+1));
        if(list_append( list, temp )!=0){
    		printf("list append failed\n");
    		return 1;
    	}
    	//a[i]=temp;
    }
    printf("the current correct list is:");
   list_print(list);
  
  
  //int b[]={0,0,0,0};
  for( int i=0; i<4; i++ ){
  	temp=(int)rand()%(i*20+1);
    	if(list_prepend( list,temp )!=0){
    		printf("list prepend failed\n");
    		return 1;
    	}
    	//b[i]=temp;
   }
  
  list_print( list );

  
  int index = 5;
  element_t* el = list_index( list, index );
  
  if( el == NULL )
    {
      printf( "index %d not found\n", index );
      return 1; // fail
    }
  
  printf( "value at index %d is %d\n", index, el->val );
  

  
  return 0; // tests pass
}




int test_element_create( void )
{
   int value = 1492; // some unusual value

 // allocate an element, fill it full of non-zero values, then free
  // it immediately
  element_t* el = malloc( sizeof( element_t ) );
  assert(el);
  memset( el, 0xFF, sizeof( element_t ) ); // 0xFF is 255 in hexadecimal
  free(el);

  // since we ask for the same size memory chunk again, we will
  // probably get the same chunk back. Since we filled it full of 255s
  // above, its next pointer will not be zero unless element_create()
  // sets it explicity. 
  el = element_create( value );
  assert(el);
  
  // check that el->next was initialized
  if( el->next )
    {
      puts( "element_create(): element->next not null" );
      return 1;
    }  
  
  // check that el->value was initialized
  if( el->val != value )
    {
      puts( "element_create(): element->val not correct" );
      return 1;
    }  
  
  return 0;
}
