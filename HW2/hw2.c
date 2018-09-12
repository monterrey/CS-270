#include <stdio.h>
#include <stdlib.h>
FILE * myfile;
int main(){
  myfile = fopen("hw2data.txt", "r");
  if(myfile){
    printf("AY \n");
    fclose(myfile);
  }
  return 0;
}
