#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<pthread.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>
#include<poll.h>
#define FIFO1 "popularfifo"
#define FIFO2 "client1"
#define perm 0666
#define TIME 2
#define MAX_LEN 50 
#define MAX_CLIENTS 10
int clientcount=0;
char clientfifos[MAX_CLIENTS][MAX_LEN];
int clientfd[MAX_CLIENTS];
fd_set rfds;
int maxfd;
struct timeval tv;	
int n;
void accept_clients()
{
 char message[MAX_LEN]="";
 int readfd;
 char arg[MAX_LEN]="";
 FILE * readptr;
 while(1)
 { 
  readfd=open(FIFO1,O_RDONLY);
  n=read(readfd,message,MAX_LEN);
  close(readfd);
  if(n>0)
  {
   strcpy(clientfifos[clientcount],message);
   strcpy(arg,"./service ");
   strcat(arg,message);
   readptr=popen(arg,"r");
   clientfd[clientcount]=fileno(readptr);
   FD_SET(fileno(readptr),&rfds);
   if(maxfd<fileno(readptr))
   maxfd=fileno(readptr);
   clientcount++;
  }
 }
}
int main()
{
 if((mkfifo(FIFO1,perm)<0)&&(errno!=EEXIST))
 {
   printf("Error in creting FIFO1");
 }
 int i;
 char message2[MAX_LEN]="";
 pthread_t t1;
 pthread_create(&t1, NULL, (void*)&accept_clients, NULL);
 tv.tv_sec=0;
 tv.tv_usec=200;
 while(1)
 {
      while(select(maxfd+1,&rfds,NULL,NULL,&tv)<=0){}
      for(i=0;i<clientcount;i++)
      {
       if(FD_ISSET(clientfd[i],&rfds))
       {
        n=read(clientfd[i],message2,MAX_LEN);
        if(n>0)
        {
         printf("logfrom_%s:%s",clientfifos[i],message2);
        }
        break;
       }
      }
 

  }
  pthread_join(t1, NULL);
}


