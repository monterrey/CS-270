#include <stdio.h>
#include <stdlib.h>
#include "qmem.h"

int main(){
  int * myInt;
  int * myInt2;
  int errc, errc2, err3, diff;
  errc = qmem_alloc(sizeof(int), (void **)&myInt);
  errc2 = qmem_alloc(sizeof(int), (void **)&myInt2);
  unsigned res;
  qmem_size(myInt, &res);
  err3 = qmem_cmp(myInt, myInt2,&diff); 
  /*errc = qmem_alloc(sizeof(int), (void **)&myInt); 
  int * myInt2;
  int err2 = qmem_alloc(sizeof(int), (void**) &myInt2);
   if(errc != 0){
  fprintf(stdout, "An error occured");
  }else{
    unsigned n ;
    qmem_size(myInt, &n);
    fprintf(stdout, "N val : %ld\n",n);
  }

  unsigned long u1, u2;
  errc = qmem_stats(&u1, &u2);
  if(errc != 0){
    fprintf(stdout, "Something went terribly wrong");
  }else{
    fprintf(stdout, "Num allocs : %ld \n Num bytes allocd : %ld \n", u1, u2);
  } 
  */
  return 0;
  
}
