#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#define buffersize 256
volatile sig_atomic_t childisready;
volatile sig_atomic_t parentisready;
volatile sig_atomic_t readfromfile;
volatile sig_atomic_t isdone;
// Typedefs
typedef char * string;
// Signal Handlers
void pshOne();
void pshTwo();
void cshOne();
void cshTwo();
// Program Functions
int parentFunc();
int childFunc();
string execCMD(string command);
string getUserInput();
string getFileName(string  processN , pid_t processID);
int strCmp( string str1, string str2);
int writeToFile(string str, string  myFilename);
int readFile(string buffer, int size, string myFileName);
int countElems(char * str, char delimeter);
char ** createArgArr(char * str, char delimeter, int args);
int intToBin(int a, string buffer, int bufferSize);
// User Functions
string hammingD(string fname,string fname2);
string nextUNumber(string u);
string longestRLE(string fname);
string checksum(string fname);
string binaryAddition(string b1, string b2);
string commandCount();
int binToInt(string binaryN);
int strToInt(string intStr);
int expN(int base, int power);
int isValidArg(int argNum, char ** argArr, string command);
int countSetBytes(int myInt);
// Strings
string childfilename;
string parentfilename;
string uinput;
char buff[buffersize];
// PIDS
pid_t parentPID;
//pid_t currPID;
pid_t childPID;

int validCMDS, invalidCMDS;
int main(){
  signal(SIGUSR1, pshOne);
  signal(SIGUSR2, pshTwo);
  parentPID = getpid();
  parentfilename = getFileName("parent", parentPID);
  childPID = fork();
  if(childPID != -1){
    if(childPID == 0){ 
  signal(SIGUSR1, cshOne);
  signal(SIGUSR2, cshTwo);

  string result;
  childfilename = getFileName("child", getpid());
  kill(parentPID,SIGUSR1);
  while(!isdone){
    while(!readfromfile){
      sleep(1);
    }
    readfromfile = 0;
    if(isdone){
      break;
    }
    readFile(buff, buffersize, parentfilename);
    result = execCMD(buff);
    writeToFile(result, childfilename);
    kill(parentPID, SIGUSR2);
    
  }
  exit(invalidCMDS);
    }
    sleep(1);
    childfilename = getFileName("child", childPID);
    while(!childisready){
    }
    while(!isdone){
      uinput = getUserInput();
      if(strCmp(uinput, "exit")){
	kill(childPID, SIGUSR2);
	break;
      }
      writeToFile(uinput, parentfilename);
      kill(childPID, SIGUSR1);
      while(!readfromfile){
	sleep(1);
      }
      readfromfile = 0;
      readFile(buff, buffersize, childfilename);
      fprintf(stdout, "ptor: %s\n", buff);
    }
    int status;
    wait(&status);
    int exitStatus = WEXITSTATUS(status);
    fprintf(stdout, "ptor: terminating with exit status %d\n",exitStatus);
    
  }
  return 0;
}

void pshOne(){
  childisready = 1;
}
void pshTwo(){
  readfromfile = 1;
}
void cshOne(){
  readfromfile = 1;
}
void cshTwo(){
  readfromfile = 1;
  isdone = 1;
}


string execCMD(string command){
  int elems = 0;
  char ** argArray;
  string response;
  if(command == NULL)
    return "No command input";
  if(*command == '\0')
    return "Empty string";
  
  
  switch(*command){
  case 'H':
    elems = countElems(command, ' ');
    if(elems == 3){
      argArray = createArgArr(command, ' ',elems);
      response = hammingD(*(argArray+1), *(argArray+2));
      validCMDS++;
      return response;
    }
    break;
  case '0':
    elems = countElems(command, ' ');
    if(elems == 2){
      argArray = createArgArr(command, ' ',elems);
      response = nextUNumber(argArray[1]);
      validCMDS++;
      return response;
    }
    break;
  case 'R':
      elems = countElems(command, ' ');
    if(elems == 2){
      argArray = createArgArr(command, ' ',elems);
      response = longestRLE(argArray[1]);
      validCMDS++;
      return response;
    }
    break;
  case 'X':
      elems = countElems(command, ' ');
    if(elems == 2){
      argArray = createArgArr(command, ' ',elems);
      response = checksum(argArray[1]);
      validCMDS++;
      return response;
    }
    break;
  case '+':
      elems = countElems(command, ' ');
    if(elems == 3){
      argArray = createArgArr(command, ' ',elems);
      response = binaryAddition(argArray[1],argArray[2]);
      validCMDS++;
      return response;
    }
    break;
  case '!':
    response = malloc(sizeof(char) * 30);
    sprintf(response,"!: %d valid %d invalid", validCMDS, invalidCMDS);
    validCMDS++;
    return response;
    break;
  default:
    invalidCMDS++;
    return "Invalid Command";
  }
  
  invalidCMDS++;
  return "invalid Command";
}
// User Functions
string hammingD(string fname,string fname2){

  FILE * f1 = fopen(fname, "r");
  unsigned long f1Size , f2Size,i=0,count=0;
  string buffer1, buffer2,buff;
  char * p1,* p2;
  char tmp;
  if(f1 != NULL){

 FILE * f2 = fopen(fname2, "r");
 if(f2 != NULL){
   fseek(f1, 0, SEEK_END);
   f1Size = ftell(f1);
   rewind(f1);
   
   fseek(f2, 0 , SEEK_END);
   f2Size = ftell(f2);
   rewind(f2);
   if(f2Size != f1Size){
     return "file size differ";}
   else{
     buffer1 = malloc(sizeof(char) * f1Size);
     buffer2 = malloc(sizeof(char) *f2Size);
     buff = malloc(sizeof(char)*30);
     fread(buffer1, sizeof(char), f1Size, f1);
     fread(buffer2, sizeof(char), f2Size, f2);
     p1 = buffer1;
     p2 = buffer2;
     for(i = 0; i <f1Size; i++){
       tmp = *(p1 + i)^*(p2+i);
       while(tmp != 0){
	 count++;
	 tmp &= tmp-1;
       }
     }
     free(buffer1);
     free(buffer2);
		   sprintf(buff,"H: Hamming distance: %ld", count);
		   return buff;
   }
   fclose(f2);
 }
 fclose(f1);
  }
  return "One or more files could not be open";
}
string nextUNumber(string u){
  int myInt = strToInt(u);
  int magN = myInt+1;
  string buff;
  buff = malloc(sizeof(char)*15);
  if(myInt == 0){
    return "Function doesn't work with 0";
  }
  int count = countSetBytes(myInt);
  int tmpT = countSetBytes(magN);
  while(tmpT != count){
    magN++;
    tmpT = countSetBytes(magN);
  }
  sprintf(buff, "0: %d", magN);
  return buff;
  
}
int strToInt(string intStr){
  if(intStr != NULL){
    int count = 0, i=0;
    int value=0;
    while(*(intStr+count) != '\0'){
      count++;
    }
    for(i=0;i<count; i++){
      value += (*(intStr+i) - 48)*(expN(10,count-i-1));
    }
    return value;
  }else{
    return -1;
  }
}

int expN(int base, int power){
  int i =0;
  int res = 1;
  
  for(i =0; i< power ; i++) {
    res = res * base;
  }
  return res;
}
int countSetBytes(int myInt){
  int tmp = 0;
    while(myInt != 0){
    tmp++;
    myInt &= myInt -1;
  }
    return tmp;
}
string longestRLE(string fname){
  unsigned long maxRun = 0, maxByteStart = 0, currRun=0, currByteStart =0, bufferSize,i;
  FILE * fp = fopen(fname, "r");
  string buffer;
  char  maxByte;
  char  currByte;
  string response;
  if(fp!=NULL){
    response = malloc(sizeof(char) * 50);
    fseek(fp, 0, SEEK_END);
    bufferSize = ftell(fp);
    rewind(fp);
    buffer = malloc(sizeof(char) * bufferSize);
    fread(buffer, sizeof(char), bufferSize, fp);
    maxByte = *buffer;
    currByte = *buffer;
    for(i=0; i<bufferSize; i++){
      if(buffer[i] == currByte){
	currRun++;
      }else{
	if(currRun > maxRun){
	  maxRun = currRun;
	  maxByte = currByte;
	  maxByteStart = currByteStart;
	}
	currRun = 1;
	currByte = buffer[i];
	currByteStart = i;
      }
    }
    fclose(fp);
    sprintf(response, "R: %ld 0x%x %ld\n",maxRun,maxByte, maxByteStart); 
    return response;
  }else{
    return "Couldn't open file";
  }
}
string checksum(string fname){
  FILE * fptr;
  fptr = fopen(fname, "r");
  if(fptr != NULL){
    string buffer;
    char* resp = malloc(sizeof(char)*10);
    char * currByte;
    int bufferSize;
    int i;
    char sum = 0;
    
    fseek(fptr, 0, SEEK_END);
    bufferSize = ftell(fptr);
    rewind(fptr);
    buffer = malloc(sizeof(char) * bufferSize);
    fread(buffer, sizeof(char), bufferSize,fptr);
    fclose(fptr);
    for(i = 0;i< bufferSize; i++){
      sum += buffer[i];
    }
    free(buffer);
    sum = (sum^255)+1;
    //fprintf(stdout,"%x\n", sum);
    sprintf(resp,"X: 0x%x",sum);
    return resp;
  }else{
    return "An error occured";
  }}
string binaryAddition(string b1, string b2){
  int binInt1 = binToInt(b1);
  int binInt2 = binToInt(b2);
  int answer = binInt1 + binInt2;
  char buff[33];
  char * resp = malloc(sizeof(char) *38);
  buff[32] = '\0';
  intToBin(answer, buff, 32);
  //  fprintf(stdout,"%d %d %d\n",binInt1, binInt2,answer); 
  sprintf(resp,"+ %s\n",buff);
  return resp;
}
int intToBin(int a, string buffer, int bufferSize){
  buffer += (bufferSize - 1);
  int i;
  for (i = 31; i >= 0; i--) {
    *buffer-- = (a & 1) + '0';
    a >>= 1;
  }
  return 1;
}
int binToInt(string binaryN){
  int length=0,i=0,j, magN, res =0;
  if(binaryN != NULL){
    while(*(binaryN+i) != '\0'){
      if(*(binaryN+i) == '1' | *(binaryN+i) == '0' ){
	i++;
      }else{
      i++;
      return -2;
      }
    }
    length = i;
    for(i = 0; i< length;i++){
      if(*(binaryN+i) == '1'){
	magN= 1;
	for(j=0;j<(length-i-1); j++){
	  magN = magN*2;
	}
	res += magN;
      }
    }
    return res;
  }
  return -1;
}


// Program functions
string getUserInput(){
  char * line = NULL;
  size_t size;
  fprintf(stdout,"cmd: ");
  if(getline(&line, &size, stdin) == -1){
    fprintf(stdout, "Something went wrong\n");
  }
  //fprintf(stdout,"size: %ld sizeof: %ld \n", size, sizeof(size_t))
    ;
  //  fprintf(stdout, "%s\n", line);
  
  return line;
}
string getFileName(string  processN , pid_t processID){
  char * fileName = malloc(25*sizeof(char));
  int n = sprintf(fileName,"ptor-%s-%d",processN, processID);
  return fileName;
}
int strCmp( string str1, string str2){
  if(str1 != NULL && str2 != NULL){
    char * p1 = str1;
    char * p2 = str2;
    while(*p1 != '\0' &&  *p2 != '\0'){
      if(*p1 != *p2){
	return 0;
      }
      p1++;
      p2++;
    }
      return 1;
  }
  
  return 0;
}
int writeToFile(string str, string myFilename){
  FILE * tmpFile;
  tmpFile = fopen( myFilename, "w");
  if(tmpFile != NULL){
    fputs(str, tmpFile);
    fclose(tmpFile);
  }
  return 0;
}
int readFile(string buffer, int size, string myFileName){
  FILE * tmpFile;
  tmpFile = fopen(myFileName,"r");
  if(tmpFile == NULL)
    return -1;
  fgets(buffer, size, tmpFile);
  fclose(tmpFile);
  return 1;
}
char ** createArgArr(char * str, char delimeter, int args){
  int i = 0, j = 0, count = 0;
  char ** tmpArr = (char **) malloc((args +1) * sizeof(char *));
  if(args > 0){
    int* tmpInt =(int *) malloc(args*sizeof(int));
    while(str[i] != '\0' ){
      if(str[i] == delimeter){
	tmpInt[j] = count;
	j++;
	count = 0;
	i++;
      }else{
      count++;
      i++;
      }
    }
    if(args > j){
      tmpInt[j] = count-1;
    }
    int counter = 0;
    for(i = 0; i < args; i++){
      tmpArr[i] = (char * ) malloc( ( tmpInt[i] +1 ) * sizeof(char));
    }
    for(i = 0 ; i< args ; i++){
	for(j = 0; j< tmpInt[i] ; j++){
	  tmpArr[i][j] = str[counter];
	  counter++;
	}
	tmpArr[i][j] = '\0';
	counter++;	
      }
    free(tmpInt);
  }
  tmpArr[args] = NULL;
  return tmpArr;
}
int countElems( char * str, char delimeter){
  int counter = 0;
  int i = 0;
  int incNext = 1;
  if(str != NULL){
  while( str[i] != '\0' ){
    if(incNext == 1){
      incNext = 0;
      counter++;
    }
    else if(str[i] == delimeter){
      incNext = 1;
    }
    i++;
  }
  }
  return counter;
}
