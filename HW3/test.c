#include <stdio.h>
#include <stdlib.h>
#include "qmem.h"

int main(){
  int * myInt;
  qmem_alloc(sizeof(int), myInt); 
  return 0;
  
}
