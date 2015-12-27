#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#define FIFO1 "server_to_client1"
#define FIFO2 "client_to_server1"
#define FIFO3 "client_to_server2"
#define FIFO4 "server_to_client2"
#define perm 0666
#define MAX_LEN 20
int main()
{
 char message[MAX_LEN]="";
 int i,n,readfd,writefd;
 pid_t pid=fork();
 if(pid==0)
 { 
  while(1)
  {
   readfd=open(FIFO2,O_RDONLY);
   strcpy(message,"");
   n=read(readfd,message,MAX_LEN);
   close(readfd);
   if(n>0)
   {
    writefd=open(FIFO1,O_WRONLY);
    if(strcmp(message,"bye")==0)
    {
     strcpy(message,"bye");
     write(writefd,message,MAX_LEN);
    }
    else
    {
     /* int length=strlen(message);
     char l[20]="";
     itoa(length,l,10);
     strcpy(message,"");
     strcat(message,"Length of the string:");
     strcat(message,l);*/
     write(writefd,message,MAX_LEN);
    }
    close(writefd);
   }
  }
 }
 else if(pid>0)
      {
       while(1)
       {
         readfd=open(FIFO3,O_RDONLY);
         strcpy(message,"");
         n=read(readfd,message,MAX_LEN);
         close(readfd);
         if(n>0)
         {
          writefd=open(FIFO4,O_WRONLY);
          if(strcmp(message,"bye")==0)
          {
           strcpy(message,"bye");
           write(writefd,message,MAX_LEN);
          }
          else
          {
           write(writefd,message,MAX_LEN);
          }
          close(writefd);
         }
       }     
      }    

       
}
