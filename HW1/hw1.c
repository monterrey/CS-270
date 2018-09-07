#include <stdio.h>
#include <stdlib.h>
int makearg( char * text , char ** arrC);

int argc;
char **argv;
char input_line[256];
int main(){
printf("Yo was good give me dat text\n");
//argc = makearg(input_line[256], argv);
fgets(input_line, 256, stdin);

argc = makearg(input_line, argv);
printf("That line contains %d words. Here they are:\n ", argc);
int i = 0;
for(i = 0; i < argc; i++){
printf(argv[i]);
printf("\n");
}

return 0;
}
int makearg( char * text, char ** arrC){
int wordCount = 0;
int maxL = 0;
int currL;
char * p1;
char * p2;
p1 = text;
p2 = text;
while(*p1 != '\0' ){
//fputs(p1, stdout);
currL++;
p1++;

if(*p1 == ' '){

while(*p1 == ' ' )
p1++;

if(currL > maxL)
maxL = currL;

currL = 0;

wordCount++;
}


}
wordCount++;
maxL++;
arrC = (char **)malloc(sizeof(char *) * wordCount);
arrC[0] = (char *)malloc(sizeof(char) * maxL * wordCount);
int k = 0;
for(k = 0; k < wordCount; k++)
	arrC[k] = (*arrC + maxL * k);
int i = 0, j =0;
while(*p2 != '\0'){
arrC[i][j] = *p2;
j++;
p2++;
if(*p2 == ' '){
while(*p2 == ' '){
p2++;}

i++;
j = 0;
}} 
argv = arrC;
return wordCount;
}
