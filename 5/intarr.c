#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* 
 * intarr.h
 *
 * Provides a bounds-checked, resizable array of integers with
 * random-access and stack interfaces, and several utility functions
 * that operate on them.
 * 
 */

/* DO NOT CHANGE THIS FILE - YOUR CODE WILL BE COMPILED AGAINST THE
   ORIGINAL. NON-COMPILING CODE WILL FAIL ALL THE TASKS!

   FOR TASKS WITH MORE THAN ONE FUNCTION, YOU MUST IMPLEMENT ALL
   FUNCTIONS TO PASS THE TASK.
*/

/* Structure type that encapsulates our safe int array. */
typedef struct {
  int* data;
  unsigned int len;
} intarr_t;

/* A type for returning status codes */
typedef enum {
  INTARR_OK,
  INTARR_BADARRAY,
  INTARR_BADINDEX,
  INTARR_BADALLOC,
  INTARR_NOTFOUND
} intarr_result_t;

/* TASK 1 */

// Create a new intarr_t with initial size len.  If successful
// (i.e. memory allocation succeeds), returns a pointer to a
// newly-allocated intarr_t.  If unsuccessful, returns a null pointer.
intarr_t* intarr_create( unsigned int len ){
  intarr_t* newarray=malloc(sizeof(intarr_t));
  newarray->data=malloc(sizeof(int)*len);
  if(!newarray) return NULL;
  else {
  	newarray->len=len;
  	return newarray;
  }
}

// frees all memory allocated for ia. If the pointer is null, do
// nothing. If the ia->data is null, do not attempt to free it.
void intarr_destroy( intarr_t* ia ){
  if(ia) 
    if(ia->data)
       free(ia);
}
/* TASK 2 */

// If index is valid, set the value at ia[index] to val and return
// INTARR_OK. Otherwise, leave the array unmodified and return
// INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_set( intarr_t* ia, 
			    unsigned int index, 
			    int val ){
	if(!ia) return INTARR_BADARRAY;
	if(index >= ia->len || index<0) return INTARR_BADINDEX;
	if(ia->data+index ) {
		*(ia->data+index) = val;
		return INTARR_OK;
	}
	return INTARR_BADINDEX;
}

// If index is valid and i is non-null, set *i to ia[index] and return
// INTARR_OK. Otherwise no not modify *i and return
// INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_get( const intarr_t* ia, 
			    unsigned int index, 
			    int* i ){
	printf("%u,%u",index,ia->len);
	if(!ia) return INTARR_BADARRAY;
	else if (!i || index<0 || index>= ia->len) return INTARR_BADINDEX;
	else {
		*i=*(ia->data+index);
		return INTARR_OK;
	}
}

/* TASK 3 */

// Return a duplicate of ia, allocating new storage for the duplicate
// data (we call this a "deep copy"). If unsuccessful (i.e. memory
// allocation for the copy fails, or ia is null), return a null pointer. 
intarr_t* intarr_copy( const intarr_t* ia ){
	if(!ia) return NULL;
	intarr_t* newia=intarr_create(ia->len);
	newia->len = ia->len;
	memcpy(newia->data,ia->data,sizeof(int)*ia->len);
	if(!newia) return NULL;
	else return newia;
}

/* TASK 4 */

// sort ia by value smallest-to-largest, so that data[i] < data[i+1]
// for all valid i, then return INTARR_OK. Works in-place: contents of
// ia are sorted on return. If ia is null, return
// INTARR_BADARRAY.
int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

intarr_result_t intarr_sort( intarr_t* ia ){
if(!ia) return INTARR_BADARRAY;
qsort(ia->data,ia->len,sizeof(ia->data[0]),compare);
return INTARR_OK;
}

/* TASK 5 */

// Find the first occurance of the target in the array, searching from
// index 0. If the target is found and i is non-null, set *i to the
// location index and return INTARR_OK. If target does not occur in
// the array, leave *i unmodified and return INTARR_NOTFOUND. If ia is
// null, return INTARR_BADARRAY.
intarr_result_t intarr_find( intarr_t* ia, int target, int* i ){
	if(!ia) return INTARR_BADARRAY;
	for(int j=0;j<ia->len;j++){
		if(*(ia->data+j)==target && i) {
			*i=j;
			return INTARR_OK;
		}
	}
	return INTARR_NOTFOUND;
}

/* TASK 6 */

// Append val to the end of ia (allocating space for it). If
// successful, return INTARR_OK, otherwise return
// INTARR_BADALLOC. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_push( intarr_t* ia, int val ){
	if(!ia) return INTARR_BADARRAY;
	intarr_t* newia=intarr_copy(ia);
	if(!newia) return INTARR_BADALLOC;
	ia->data=malloc(sizeof(int)*(ia->len+1));
	ia->len++;
	memcpy(ia->data,newia->data,sizeof(int)*newia->len);
	*(ia->data+newia->len)=val;
	free(newia);
	return INTARR_OK;
}

// If the array is not empty, remove the value with the highest index
// from the array, and, if i is non-null, set *i to the removed value,
// then return INTARR_OK. If the array is empty, leave *i unmodified
// and return INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_pop( intarr_t* ia, int* i ){
	if(!ia) return INTARR_BADARRAY;
	if(!ia->data) return INTARR_BADINDEX;
	if(!i) return INTARR_BADINDEX;
	if(ia->len>0){
		intarr_get(ia,ia->len-1,i);
		intarr_t* newia=intarr_copy(ia);
		free(ia->data);
		ia->data=malloc(sizeof(int)*(ia->len-1));
		memcpy(ia->data,newia->data,sizeof(int)*(newia->len-1));
		ia->len--;
		free(newia);
	}
	else return INTARR_BADINDEX;
	return INTARR_OK;
}

/* TASK 7 */

// Resize ia to contain newlen values. If newlen is less than the
// original array length, the end of the array is discarded. If newlen
// is greater than the original array length, intialize all the new
// integers to zero. If the allocation is successful, return
// INTARR_OK, otherwise return INTARR_BADALLOC. If ia is null, return
// INTARR_BADARRAY.
intarr_result_t intarr_resize( intarr_t* ia, unsigned int newlen ){
	if(!ia) return INTARR_BADARRAY;
	if(!ia->data) return INTARR_BADARRAY;
	intarr_t* newia=intarr_copy(ia);
	if(!newia) return INTARR_BADALLOC;
	free(ia->data);
	ia->data=malloc(sizeof(int)*newlen);
	if(newlen>ia->len){
		memcpy(ia->data,newia->data,sizeof(int)*ia->len);
		memset(ia->data+ia->len,0,newlen-ia->len);
	}
	else memcpy(ia->data,newia->data,sizeof(int)*newlen);
	free(newia);
	ia->len=newlen;
	return INTARR_OK;
}

/* TASK 8 */

// Get a deep copy of a portion of ia from index first to index last
// inclusive. If successful, return a pointer to a newly-allocated
// intarr_t containing a copy of the specfied section. If an error
// occurs, i.e. ia is null, first or last are out of bounds, last <
// first, or memory allocation fails, return a null pointer.
intarr_t* intarr_copy_subarray( intarr_t* ia, 
				unsigned int first, 
				unsigned int last ){
	if(!ia || first>last) return NULL;
	intarr_t * newarray=malloc(sizeof(newarray));
	newarray->len=(last-first+1);
        newarray->data=malloc(sizeof(int)*newarray->len);
	if(!newarray->data) return NULL;
	for(int i=0;i<newarray->len;i++){
		*(newarray->data+i)=*(ia->data+i+first);
	}
	return newarray;
}







