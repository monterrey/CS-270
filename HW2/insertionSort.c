#include <stdio.h>
#include <stdlib.h>
#include "hw2.h"
#include "insertionSort.h"
#include "bubbleSort.h"

void insertionSort( char myArr[LINECOUNT][CHARCOUNT]){
  char key[CHARCOUNT];
  int i,j;
  for(i=1; i<LINECOUNT; i++){
    copyString(myArr[i] , key);
    j = i-1;
    while(j>=0 && (compareA(myArr[j] , key) > 0 )){
	  swapA(myArr[j+1], myArr[j]);
	  j = j-1;
      }
      copyString(key,  myArr[j+1]);
  }
}
void copyString( char s1[CHARCOUNT], char s2[CHARCOUNT]){
  int i;
  for(i = 0 ; i< CHARCOUNT; i++)
    s2[i]  = s1[i];
}
