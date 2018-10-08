#include <stdio.h>
#include <stdlib.h>
#include "qmem.h"

int main(){
  int * myInt;
  //fprintf(stdout, "myInt Val %d\n", *myInt);
  fprintf(stdout, "size of int: %d\n",(int) sizeof(int));
  int errc;
  errc = qmem_alloc(sizeof(int), (void **)&myInt); 
  if(errc != 0){
  fprintf(stdout, "An error occured");
  }else{
    fprintf(stdout, "myInt Val %d\n", *(myInt+1));
  }




  unsigned long u1, u2;
  errc = qmem_stats(&u1, &u2);
  if(errc != 0){
    fprintf(stdout, "Something went terribly wrong");
  }else{
    fprintf(stdout, "Num allocs : %ld \n Num bytes allocd : %ld \n", u1, u2);
  } 
  return 0;
  
}
