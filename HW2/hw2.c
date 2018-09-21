#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hw2.h"
#include "bubbleSort.h"
#include "quickSort.h"
#include "insertionSort.h"
#include <time.h>
FILE * myfile;
const int charC = 256;
const int lineC = 20;
//int CHARCOUNT = charC;
//int LINECOUNT = lineC;
char myArr[LINECOUNT][CHARCOUNT];
char backUp[LINECOUNT][CHARCOUNT];
void duplicateArr();
bool createArray();
time_t start_t, end_t;
double diff_t;

int main(){
  if(createArray() == true){
    	//char ** myArrPtr = myArr;
    	duplicateArr();
	time(&start_t);
    	bubbleSort(backUp , LINECOUNT );
    	time(&end_t);
	diff_t = difftime(end_t, start_t);
	fprintf(stdout, "Bubble sort took %f seconds to complete\n", diff_t);
	duplicateArr();
	//createArray();
	time(&start_t);
	insertionSort(backUp);
	time(&end_t);
	diff_t = difftime(end_t, start_t);
	fprintf(stdout, "Insertion sort took %f seconds to complete \n", diff_t);
	duplicateArr();
	time(&start_t);
	quickSort(backUp,0 , LINECOUNT);
	time(&end_t);
	diff_t = difftime(end_t, start_t);
	fprintf(stdout, "Quick sort took %f seconds to complete\n", diff_t);	
	//createArray();
	////quickSort(myArr, 0, LINECOUNT);
    //int i;
    //for(i = 0; i<LINECOUNT; i++)
      //fprintf(stdout, "%c\n", myArr[i][0]);
  }
  return 0;
}

void duplicateArr(){
int i,j;
for( i = 0; i< LINECOUNT; i++){
for(j= 0; j<CHARCOUNT; j++){
backUp[i][j] = myArr[i][j];
}
}
}
bool createArray(){
  myfile = fopen("hw2data.txt", "r");
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
