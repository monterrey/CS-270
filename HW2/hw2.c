#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hw2.h"
#include "quickSort.h"
FILE * myfile;
const int charC = 256;
const int lineC = 20;
int CHARCOUNT = charC;
int LINECOUNT = lineC;
char myArr[lineC][charC];
bool createArray();
int main(){
  if(createArray() == true){
    //char ** myArrPtr = myArr;
    quickSort(myArr, 0, LINECOUNT);
    int i;
    for(i = 0; i<LINECOUNT; i++)
      fprintf(stdout, "%c\n", myArr[i][0]);
  }
  return 0;
}


bool createArray(){
  myfile = fopen("data/data1.txt", "r");
  int i , j;  
  if(myfile){
    for(i = 0; i < LINECOUNT; i++){
      do{
	myArr[i][j] = (char) fgetc(myfile);
	//fprintf(stdout, "%c", myArr[i][j]);
	j++;
      }while(j<(CHARCOUNT-1));
      myArr[i][j+1] = '\0';
      if(i<(LINECOUNT-1))
	fgetc(myfile);
      
      //fprintf(stdout, "\n");
      //fprintf(stdout, "I val : %d J val : %d ", i, j);
      j=0;
    }
    fclose(myfile);
    //printf("Char count val: %d\n", CHARCOUNT);
    /*for(i =0; i<CHARCOUNT ; i++)
      printf("%c", myArr[19][i]);
      printf("\n");*/
    return true;
  }else{
    fprintf(stderr, "An error occured and the file couldn't be opened");
    return false;
  }  
}
