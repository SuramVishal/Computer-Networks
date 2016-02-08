#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<pthread.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/shm.h>
#include<signal.h>
#define FIFO1 "popularfifo"
#define FIFO2 "client1"
#define perm 0666
#define TIME 2
#define MAX_LEN 50
#define size 50
char *x;
char *y;
void handler()
{
 printf("Service has been releived");
}
int main(int argc,char *argv[])
{
 if((mkfifo(FIFO1,perm)<0)&&(errno!=EEXIST))
 {
   printf("Error in creting FIFO1");
 }
 int shmid1=shmget(7123,size,IPC_CREAT|0666);
 int shmid2=shmget(7124,size,IPC_CREAT|0666);
 x=shmat(shmid1,NULL,0);
 y=shmat(shmid2,NULL,0);
 int i;
 int readfd;
 FILE * readptr;
 pid_t pid1;
 int n;
 char message[MAX_LEN]="";
 char message2[MAX_LEN]="";
 char arg[MAX_LEN]="";
 signal(SIGUSR1,handler);
 while(1)
 {
     readfd=open(FIFO1,O_RDONLY);
     n=read(readfd,message,MAX_LEN);
     printf("%s",message);
     close(readfd);
     if(n>0)
     {  
     strcpy(x,message);   
     sprintf(y,"%d",getpid());
     printf("Hello");
     kill(atoi(argv[1]),SIGUSR1);
     }

  }
}
