#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<pthread.h>
#define FIFO1 "client_to_server2"
#define FIFO2 "server_to_client2"
#define perm 0666
#define TIME 2
#define MAX_LEN 20


void clienttoserver()
{
    char message[MAX_LEN]="";
    int flag=0;
    int i;
    while(1)
    {
     read(0,message,MAX_LEN);
     for(i=0;i<strlen(message);i++)
     {
      if(flag==1)
      message[i]='\0';
      if(message[i]=='\n')
      flag=1;
     }
     flag=0;
     int cs=open(FIFO1,O_WRONLY);
     write(cs,message,MAX_LEN);
     close(cs);
     strcpy(message,"");
    }

}
void servertoclient()
{
 char message[MAX_LEN]="";
 while(1)
 {
    int sc=open(FIFO2,O_RDONLY);
    strcpy(message,"");
    int n=read(sc,message,MAX_LEN);
    if(n>0)
    printf("%s",message);
    close(sc);
 }
}
int main()
{
 if((mkfifo(FIFO1,perm)<0)&&(errno!=EEXIST))
  {
   printf("Error in creting FIFO1");
  }
  if((mkfifo(FIFO2,perm)<0)&&(errno!=EEXIST))
  {
   printf("Error in creating FIFO2");
  }
  pthread_t t1,t2;
  pthread_create(&t1, NULL, (void*)&servertoclient, NULL);
  pthread_create(&t2, NULL, (void*)&clienttoserver, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
}
