#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<pthread.h>
#include<stdio.h>
#define FIFO1 "popularfifo"
#define perm 0666
#define TIME 2
#define MAX_LEN 50
int main(int argc,char *argv[])
{
 
 int writefd;
 char clientfifo[50];
 strcpy(clientfifo,"Hello ");
 strcat(clientfifo,argv[1]); 
 strcat(clientfifo,".This is Service here\n");
 writefd=open(argv[1],O_WRONLY);
 write(writefd,clientfifo,50);
 printf("%s\n",clientfifo);
 close(writefd);
 
}
