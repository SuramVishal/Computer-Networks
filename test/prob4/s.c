#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<pthread.h>
#include<stdio.h>
#include <signal.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/shm.h>
#define FIFO1 "popularfifo"
#define perm 0666
#define TIME 2
#define MAX_LEN 50
#define size 50
char *x;
char *y;
void handler()
{
  int writefd;
  char clientfifo[50];
  strcpy(clientfifo,"Hello ");
  strcat(clientfifo,x); 
  strcat(clientfifo,".This is Service here\n");
  strcat(clientfifo,y);
  writefd=open(x,O_WRONLY);
  write(writefd,clientfifo,50);
  close(writefd);
  printf("pid %d",atoi(y));
  kill(atoi(y),SIGUSR1);
}
int main(int argc,char *argv[])
{
 printf("my pid %d",getpid());
 signal(SIGUSR1,handler);
 int shmid1=shmget(7123,size,IPC_CREAT|0666);
 int shmid2=shmget(7124,size,IPC_CREAT|0666);
 x=shmat(shmid1,NULL,0);
 y=shmat(shmid2,NULL,0);
 while(1)
 {
  
 }

 
}
