#include <stdio.h>
#include <stdlib.h>
static unsigned long allocations;
static unsigned long bytes_alloced;
int is_valid(void * data);
int qmem_alloc(unsigned num_bytes, void ** rslt){
    unsigned offset= sizeof(char)*4 + sizeof(unsigned);
    *rslt = (void *) malloc(offset+num_bytes);
    //*(rslt + 1) = (void *) malloc (num_bytes);
    if(rslt == NULL){
    return -1;
    }
   char * ptr  = (char *)*rslt;// + num_bytes;
   *ptr = 'l';
   ptr++;
   *ptr = 'u';
   ptr++;
   *ptr = 'i';
   ptr++;
   *ptr = 's';
   ptr++;
   unsigned * bytesAlloc = (unsigned *) ptr;
   *bytesAlloc = num_bytes;
   allocations += 1;
   bytes_alloced += offset+ num_bytes;
  return 0;
  
}
int qmem_allocz(unsigned num_bytes, void ** rslt){
  unsigned offset= sizeof(char)*4 + sizeof(unsigned);
  *rslt = (void *) calloc(offset, 1);
  *(rslt +1) = (void *)  calloc(num_bytes, 1);
  if(rslt == NULL){
    return -1;
  }
   char * ptr  = (char *)*rslt;// + num_bytes;
   *ptr = 'l';
   ptr++;
   *ptr = 'u';
   ptr++;
   *ptr = 'i';
   ptr++;
   *ptr = 's';
   ptr++;
   unsigned * bytesAlloc = (unsigned *) ptr;
   *bytesAlloc = num_bytes;
   allocations += 1;
   bytes_alloced += offset+ num_bytes;
  return 0;
}
int qmem_allocv(unsigned num_bytes, int mark, void ** rslt){
  if(sizeof(char) != 1)
    return -2;
  int i;
  char lowerbits = (char) mark;
  unsigned offset= sizeof(char)*4 + sizeof(unsigned);
  //unsigned totalSize = num_bytes + offset;
  *rslt = (void *) malloc(offset);
  *(rslt +1) = (void *) malloc(num_bytes);
  if(rslt == NULL){
    return -1;
  }
   char * ptr  = (char *)*rslt;// + num_bytes;
   *ptr = 'l';
   ptr++;
   *ptr = 'u';
   ptr++;
   *ptr = 'i';
   ptr++;
   *ptr = 's';
   ptr++;
   unsigned * bytesAlloc = (unsigned *) ptr;
   *bytesAlloc = num_bytes;
   char * setM = (char *) *(rslt+1);
  for(i = 0; i< (int) num_bytes; i++){
    *(setM+i) = lowerbits;
  }
   allocations += 1;
   bytes_alloced += offset+ num_bytes;
  return 0;
}
int qmem_free(void ** data){
  if(data == NULL)
    return -2;
  if(*data == NULL)
    return -1;
  int validity = is_valid( *data);
  if( validity != 1)
    return -3;
  char * setter = (char *)*data;
  setter = '\0';
  free(*(data+1));
  free(*(data));
  fprintf(stdout, "Status : %d ", validity);
  return 0;
}
int qmem_cmp(void * p1, void * p2, int * diff){
  //  fprintf(stdout, "Int val : %d ", is_valid(p1) );
  if(is_valid(p1) == 1 && is_valid(p2))
    fprintf(stdout, "valid \n");
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
  if(data == NULL)
    return -1;
  if(rslt == NULL)
    return -2;

  if(is_valid(data)){
    char * ptr = (char *) data;
    ptr += 4;
    unsigned * tmp = (unsigned *) ptr;
    *rslt = *tmp;
    //fprintf(stdout,"is valid: %ld \n", *rslt);
  }else{
    return -3;
  }
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

int is_valid(void * data){
  int valid_flag = 1;
  char * ptr = (char *) data ;
  fprintf(stdout, "fchar : %c \n", *ptr);
  char * str = "luis";
  int i;
  for(i =0 ; i < 4; i++){
    if(*(ptr+i) != str[i]){
      return 0;
    }
    
  }
  return 1;
}
