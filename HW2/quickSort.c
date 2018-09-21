#include <stdio.h>
#include <stdlib.h>
#include "quickSort.h"
#include "hw2.h"
#include "bubbleSort.h"

void quickSort(char myArr[LINECOUNT][CHARCOUNT] , int first, int last){
  int piv ;
  if(first < last){
    piv = pivot(myArr , first, last);
    quickSort(myArr, first, piv-1);
    quickSort(myArr, piv+1, last);
  }
}

int pivot(char myArr[LINECOUNT][CHARCOUNT], int first, int last){
  int p = first;
  int pivot = first;
  int i;
  for(i = first+1; i<=last; i++){
    if(compareA(myArr[i], myArr[pivot]) <= 0 ){
      p++;
      swapA(myArr[i], myArr[p]);
    }
  }
  swapA(myArr[p], myArr[first]);
  //fprintf(stdout,"P: %d", p);
  return p;
  
}
/*
int quickSort(char ** arrPTR, int first , int last){
  int piv;
  if(first < last){
    piv = pivot(arrPTR, first, last);
    quickSort(arrPTR, first , piv-1);
    quickSort(arrPTR, piv+1, last);
  }
  return 0;
}
int pivot(char ** arrPTR , int first , int last){
  int p = first;
  int pivot = first;
  int i;
  for(i = first+1; i <= last ; i++){
    if(compare(arrPTR, i, pivot)<= 0){
      //fprintf(stdout, "MADE SWAP");
      p++;
	swap(arrPTR, i, p);
      }	
  }
  swap(arrPTR, p, first);
  return p;
}
int compare(char ** arrPTR, int fLineIndex, int sLineIndex){
  char FLC, SLC;
  int i;
  for(i=0; i<CHARCOUNT;i++){
    FLC = *((char*)arrPTR + fLineIndex*CHARCOUNT + i);
    SLC = *((char*)arrPTR + sLineIndex*CHARCOUNT + i);
    if(FLC> SLC )
      return 1;
    else if(SLC > FLC )
      return -1;
  }
  return 0;
}

void swap(char **arrPTR, int line1, int line2){
  char FLC, SLC, TMP;
  int i;
  for(i=0; i< CHARCOUNT; i++){
    FLC = *((char*)arrPTR + line1 * CHARCOUNT + i);
    SLC = *((char*)arrPTR + line2 * CHARCOUNT + i);
    *((char*)arrPTR + line1 * CHARCOUNT + i) = SLC;
    *((char*)arrPTR + line2 * CHARCOUNT + i) = FLC;}}
    */
