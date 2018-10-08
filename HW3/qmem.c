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
  *rslt = (void *) calloc(offset+num_bytes, 1);
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
  *rslt = (void *) malloc(offset+num_bytes);
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
  unsigned offset = (sizeof(char)*4)+ sizeof(unsigned);
  unsigned s1, s2;
  int err1, err2, i, minSize,maxSize;
  int isEqual = 1;
  err1 = qmem_size(p1,&s1);
  err2 = qmem_size(p1,&s2);
  char * ptr1 = (char *) p1;
  char * ptr2 = (char *) p2;
  ptr1 += offset;
  ptr2 += offset;
  if(s1 == s2){
    minSize = s1;
    maxSize = s2;
  }else if(s1>s2){
    minSize = s2;
    maxSize = s1;
  }else{
    minSize = s1;
    maxSize = s2;
  }
  for(i = 0; i<minSize ; i++){
    if(*(ptr1+i) != *(ptr2+i) ){
      return 0;
    }
  }
  *diff =  maxSize - minSize;
  return isEqual;
  //fprintf(stdout, "s1 : %ld , s2 : %ld", s1, s2);
  //if(is_valid(p1) == 1 && is_valid(p2))
  //  fprintf(stdout, "valid \n");
}
int qmem_cpy(void * dst, void * src){
  unsigned offset = (sizeof(char)*4)+ sizeof(unsigned);
  unsigned s1, s2;
  int err1, err2, i;
  if(dst == NULL)
    return -1;
  if(src == NULL)
    return -2;
  err1 = qmem_size(dst,&s1);
  err2 = qmem_size(src,&s2);
  if(err1 == -3)
    return -3;
  if(err2 == -3)
    return -4;
  if(&dst == &src)
    return -5;
  if(s1 != s2)
    return -6;
  char * ptr1 = (char *) dst;
  char * ptr2 = (char *) src;
  ptr1 += offset;
  ptr2 += offset;
  for(i = 0; i<s1; i++){
    *(ptr1+i) = *(ptr2+i);
  }
  return 0;
}
int qmem_scrub(void * data){
  if(data == NULL)
    return -1;
  int errc,i;
  unsigned leng;
  errc = qmem_size(data, &leng);
  if(errc == -3)
    return -2;
    unsigned offset = (sizeof(char)*4)+ sizeof(unsigned);
    char * ptr = (char *) data;
    ptr += offset;
    for(i = 0;i < leng; i++){
      *(ptr +1) = '0';
    }
  return 0;
}
int qmem_scrubv(void * data, int mark){
  if(data == NULL)
    return -1;
  int errc,i;
  unsigned leng;
  char cmark = (char) mark;
  errc = qmem_size(data, &leng);
  if(errc == -3)
    return -2;
    unsigned offset = (sizeof(char)*4)+ sizeof(unsigned);
    char * ptr = (char *) data;
    ptr += offset;
    for(i = 0;i < leng; i++){
      *(ptr +1) = cmark;
    }
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
  char * str = "luis";
  int i;
  for(i =0 ; i < 4; i++){
    if(*(ptr+i) != str[i]){
      return 0;
    }
    
  }
  return 1;
}
