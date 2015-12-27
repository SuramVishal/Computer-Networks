#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#define FIFO1 "client_to_server1"
#define FIFO2 "server_to_client1"
#define perm 0666
#define TIME 2
#define MAX_LEN 20
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

 int i,j;
 char message[MAX_LEN]="";
 pid_t pid=fork();
 if(pid==0)
 {
  while(1)
  {
   usleep(800);
   printf("Client1:");
   fgets(message,MAX_LEN,stdin);
   message[strlen(message)-1]='\0';
   int cs=open(FIFO1,O_WRONLY);
   write(cs,message,MAX_LEN);
   close(cs);
   if(strcmp(message,"bye")==0)
   break;
  }
  printf("Client Off\n");
 }
 else if(pid>0)
      {
        while(1)
        {
          int sc=open(FIFO2,O_RDONLY);
          strcpy(message,"");
          int n=read(sc,message,MAX_LEN);
          close(sc);
          if(n>0)
          {
           printf("Server:%s\n",message);
          }
          else if(strcmp(message,"bye\n")==0)
               {
                printf("Server:%s\n",message);
                break;
               }
        }
        
      }
     
}
