#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<pthread.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#define FIFO1 "popularfifo"
#define FIFO2 "client3"
#define perm 0666
#define TIME 2
#define MAX_LEN 50
int main()
{
 int readfd,writefd,n;
 if((mkfifo(FIFO1,perm)<0)&&(errno!=EEXIST))
  {
   printf("Error in creting FIFO1");
  }
  if((mkfifo(FIFO2,perm)<0)&&(errno!=EEXIST))
  {
   printf("Error in creating FIFO2");
  }
  printf("Sending request for service....\n");
  char message[MAX_LEN]="";
  strcpy(message,"client3");
  writefd=open(FIFO1,O_WRONLY);
  write(writefd,message,MAX_LEN);
  close(writefd);
  readfd=open(FIFO2,O_RDONLY);  
  while(n=read(readfd,message,50)>0){}
  close(readfd);
  printf("%s",message);
     
}

