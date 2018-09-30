#include <stdio.h>
#include <stdlib.h>

int qmem_alloc(unsigned num_bytes, void ** rslt){
  rslt = (void **) malloc((num_bytes+2));
  void ** endPtr = rslt + num_bytes;
  
  fprintf(stdout, " MI VAl: %d", (int) num_bytes);
  fprintf(stdout, "Address to start of allocated space : 0x%0X\n address of end : 0x%0X\n",
	  (unsigned) &rslt,(unsigned) &endPtr);
  return 0;
}
int qmem_allocz(unsigned num_bytes, void ** rslt){
  return 0;
}
int qmem_allocv(unsigned num_bytes, int mark, void ** rslt){
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
  return 0;
}
