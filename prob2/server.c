#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<pthread.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>
#define FIFO1 "popularfifo"
#define FIFO2 "client1"
#define perm 0666
#define TIME 2
#define MAX_LEN 50
int main()
{
 if((mkfifo(FIFO1,perm)<0)&&(errno!=EEXIST))
 {
   printf("Error in creting FIFO1");
 }
 int i;
 int readfd;
 pid_t pid1;
 int n;
 char message[MAX_LEN]="";
 while(1)
 {
     readfd=open(FIFO1,O_RDONLY);
     n=read(readfd,message,MAX_LEN);
     close(readfd);
     if(n>0)
     {    
     pid1=fork();
     if(pid1>0)
     {
     }
     else
     {
      char *newarg[3];
      newarg[0]="service";
      newarg[1]=message;
      newarg[2]=NULL;     
      char *newenviron[]={NULL};
      execve("service",newarg,newenviron);
     }
     }

  }
}
