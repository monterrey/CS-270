/* Luis Lopez
 * CS 270
 * HW 5
 * The date
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>

#define MAX_RESP_LEN (65536)
struct freqC{
  char val;
  int count;
};

void execFlag(char userflag, char * str);
void reversestr(char * str);
void sortstr(char * str);
void strfreq(char * str);

int Pivot( char * a, int first, int last);
void Quicksort( char * a, int first, int last );
void  Swap( char *v1, char * v2 );

char * genReqStr(char * website, char * resource);
// appends str2 to str 
char * concatStrings(char ** strArr, int strCount);
char msg_buf[MAX_RESP_LEN];
char flag;
int
main(argc, argv)
    int argc;
    char * argv[];
{
  if(argc < 3 || argc > 4){
    printf("Make sure that you specify the correct number of arguments in the following format:\n get-any hostname resource -[FIS]\n");
    exit(-1);
  }
  if(argc == 4 && strlen(argv[3]) != 2){
    printf("Make sure to append a - charachter before your flag, and only use one flag at a time \n");
    exit(-1);
  }
  if(argc == 4){
    flag = argv[3][1];
    if(flag != 'F' && flag != 'I'  && flag != 'S'){
      printf("Not valid flag\n");
      exit(-1);
    }
  }else{
    flag = 'D';
  }
  char * getReq = genReqStr(argv[1], argv[2]);
  printf("%s", getReq);
  //printf("GET / HTTP/1.1\r\nHost: www.example.com\r\nUser-Agent: Mozilla/5.0 (compatible; MSIE 8.0; Windows NT 6.0)\r\nReferer: \r\nConnection: Close\r\n\r\n");
  int newsocket;
    ssize_t length;
    struct timeval timeout;
    unsigned long total_length;
    struct addrinfo hints, *result;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    /*
     * resolve hostname to IP address: specify host and port num
     * (port num as string, not int)
     */

    if (getaddrinfo(argv[1], "80", &hints, &result) != 0)
    {
        freeaddrinfo(result);
        perror("getaddrinfo: ");
        exit(-1);
    }

    /*
     * create socket
     */
    if ((newsocket = socket(result->ai_family, result->ai_socktype, 0)) == -1)
    {
        perror("socket: ");
        freeaddrinfo(result);
        close(newsocket);
        exit(-1);
    
}
    /*
     * set socket timeouts
     */
    memset(&timeout, 0, sizeof(timeout));
    timeout.tv_sec = 60;
    timeout.tv_usec = 0;
    /* set timeout for a SEND */
    setsockopt(newsocket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    /* set timeout for a RECV */
    setsockopt(newsocket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    /*
     * connect to website
     */
    if (connect(newsocket, result->ai_addr, result->ai_addrlen) == -1)
    {
        perror("connect: ");
        freeaddrinfo(result); // free addrinfo memory
        close(newsocket);
        exit(-1);
    }

    /*
     * send an HTTP GET request
     */
    if ((send(newsocket,  getReq , strlen(getReq), 0)) == -1) 
    {
        perror("send: ");
        freeaddrinfo(result);
        close(newsocket);
        exit(-1);
    }

    /*
     * read webpage from connection
     */
    total_length = 0UL;
    for (;;)
    {
        length = recv(newsocket, msg_buf, MAX_RESP_LEN-1, 0);
        if (length <= 0)
            break;
        msg_buf[length] = 0;
        fprintf(stdout, "%s", msg_buf);
	
        total_length += length;
    }
    if(flag != 'D'){
    execFlag(flag, msg_buf);
    }
    printf("\n");
    printf("final status: %ld.\n", length);
    printf("read %ld chars.\n", total_length);

    if (length == -1)
    {
        perror("recv: ");
        freeaddrinfo(result);
        close(newsocket);
        exit(-1);
    }

    /*
     * free addrinfo memory
     */
    freeaddrinfo(result);

    /*
     * close socket
     */
    close(newsocket);

    return 0;
}

char * genReqStr(char * website, char * resource){
  char * linereq = "GET %s HTTP/1.1\r\nHost: %s\r\nUser-Agent: Mozilla/5.0 (compatible; MSIE 8.0; Windows NT 6.0)\r\nReferer: \r\nConnection: Close\r\n\r\n";
  int resplen = strlen(linereq) + strlen(website) + strlen(resource);
  char * resp = malloc((sizeof(char) * resplen) + 2);
  
  snprintf(resp,resplen, "GET %s HTTP/1.1\r\nHost: %s\r\nUser-Agent: Mozilla/5.0 (compatible; MSIE 8.0; Windows NT 6.0)\r\nReferer: \r\nConnection: Close\r\n\r\n", resource, website);
  return resp;
}
void execFlag(char userflag, char * str){
  switch(userflag){
  case 'I':
    reversestr(str);
    break;
  case 'S':
    sortstr(str);
    break;
  case 'F':
    strfreq(str);
    break;
  default:
    printf("Something went wrong\n");
    exit(-1);
  }
  
}
void reversestr(char * str){
  int len = strlen(str);
  int tail = len -1, head = 0, k = len/2,i;
  char tmp ;
  for(head = 0; head <= k; head++, tail--){
    tmp = str[head];
    str[head] = str[tail];
    str[tail] = tmp;
  }
  printf("%s", str);
}
void sortstr(char * str){
  int last = strlen(str) -1;
  Quicksort(str, 0, last);
  printf("%s",str);
}
void strfreq(char * str){
  struct freqC table[256];
  int len = strlen(str), index, i = 0;
  memset(table, 0, sizeof(struct freqC) * 256);
  for(i = 0; i< len; i++){
    index = (int )str[i];
    if(table[index].count == 0){
      table[index].val = str[i];
      table[index].count = 1;
    }else{
      table[index].count += 1;
    }
  }
    
  for(i=0; i<256; i++){
    if(table[i].count > 0 ){
      printf("'%c' = %d\n", table[i].val, table[i].count);
    }
  }
}


//Sort fun

void Quicksort( char * a, int first, int last )
{
    int pivot;
    if( first < last ) {
        pivot = Pivot( a, first, last );
        Quicksort( a, first, pivot-1 );
        Quicksort( a, pivot+1, last);
    }
}


/*  Pivot:  Find and return the index of pivot element.                                                                                                                                                     
 */

int Pivot( char * a, int first, int last)
{
    int  p = first;
    char pivot = a[first];
int i;
    for(  i = first+1 ; i <= last ; i++ ) {
        if( a[i] <= pivot ) {
            p++;
            Swap( &a[i], &a[p] );
        }
    }
    Swap( &a[p], &a[first] );

    return p;
}
void  Swap( char * v1, char * v2 )
{
    char  tmpVal;
    tmpVal = *v1;
    *v1 = *v2;
    *v2 = tmpVal;
}
