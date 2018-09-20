#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "hw2.h"
void swapA(char s1[CHARCOUNT], char s2[CHARCOUNT]);
int compareA(char s1[CHARCOUNT], char s2[CHARCOUNT]);

void bubbleSort(char myArr[LINECOUNT][CHARCOUNT], int n ){
  int i, j;
  for(i=0;i < n-1; i++)
    for(j=0; j<n-i-1; j++)
      if(compareA(myArr[j], myArr[j+1]) == 1 )
	swapA(myArr[j], myArr[j+1]);
}

void swapA(char s1[CHARCOUNT], char s2[CHARCOUNT]){
  int i;
  char tmp;
  for(i =0; i< CHARCOUNT; i++){
    tmp = s2[i];
    s2[i] = s1[i];
    s1[i] = tmp;
  }
}
int compareA(char s1[CHARCOUNT] , char s2[CHARCOUNT] ){
  for(int i =0; i < CHARCOUNT; i++){
    if(s1[i] < s2[i])
      return -1;
    else if(s2[i] < s1[i])
      return 1;
  }
  return 0;
}
