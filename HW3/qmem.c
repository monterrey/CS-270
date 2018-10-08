#include <stdio.h>
#include <stdlib.h>
static unsigned long allocations;
static unsigned long bytes_alloced;
int qmem_alloc(unsigned num_bytes, void ** rslt){
    unsigned offset= sizeof(int)*2 + sizeof(unsigned);
    *rslt = (void *) malloc((num_bytes+offset));
    if(rslt == NULL){
    return -1;
    }
   int * ptr  = (int *)*rslt;// + num_bytes;
   *ptr = 1997;
   ptr++;
   *ptr = 1997;
   ptr++;
   unsigned * bytesAlloc = (unsigned *) &ptr;
   *bytesAlloc = num_bytes;
   allocations += 1;
   bytes_alloced += offset+ num_bytes;
  return 0;
  
}
int qmem_allocz(unsigned num_bytes, void ** rslt){
  if(rslt == NULL){
    return -1;
  }else{
  unsigned offset= sizeof(int)*4;
  *rslt = (void *) calloc(num_bytes+offset, 1);
   int * Mark  = (int *)*rslt;// + num_bytes;
   *Mark = 6;
   *(Mark +1 ) = 3;
   *(Mark + 2 ) = 1997;
   *(Mark + 3 ) = 2018;  
  return 0;
  }
}
int qmem_allocv(unsigned num_bytes, int mark, void ** rslt){
  if(sizeof(char) != 1)
    return -2;
  int i;
  char lowerbits = (char) mark;
  unsigned offset= sizeof(int)*4;
  unsigned totalSize = num_bytes + offset;
  *rslt = (void *) malloc(totalSize);
  char * ptr = (char *) *rslt;
  for(i = offset; i< (int) totalSize; i++){
    *(ptr+i) = lowerbits;
  }
  return 0;
}
int qmem_free(void ** data){
  
  return 0;
}
int qmem_cmp(void * p1, void * p2, int * diff){
  return 0;
}
int qmem_cpy(void * dst, void * src){
  return 0;
}
int qmem_scrub(void * data){
  return 0;
}
int qmem_scrubv(void * data, int mark){
  return 0;
}
int qmem_size(void * data, unsigned * rslt){
  return 0;
}
int qmem_stats(unsigned long * num_allocs, unsigned long * num_bytes_alloced){
  if(num_allocs == NULL){
    return -1;
  }else if(num_bytes_alloced == NULL){
    return -2;
  }else{
    *num_allocs = allocations;
    *num_bytes_alloced = bytes_alloced;
    return 0;
  }
}
