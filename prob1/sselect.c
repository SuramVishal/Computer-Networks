#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<pthread.h>
#include <poll.h>
#include<time.h>
#define FIFO2 "server_to_client1"
#define FIFO1 "client_to_server1"
#define FIFO3 "client_to_server2"
#define FIFO4 "server_to_client2"
#define FIFO5 "client_to_server3"
#define FIFO6 "server_to_client3"
#define perm 0666
#define MAX_LEN 20

 char message[MAX_LEN]="";
 int i,n,readfd1,readfd2,readfd3,writefd1,writefd2;
void c1response()
{
  fd_set rfds;
  struct timeval tv;	
  tv.tv_sec=0;
  tv.tv_usec=200;
  readfd1=open(FIFO1,O_RDONLY);
  readfd2=open(FIFO3,O_RDONLY);
  readfd3=open(FIFO5,O_RDONLY);
  int maxfd=readfd1;
  if(maxfd<readfd2)
  maxfd=readfd2;
  if(maxfd<readfd3)
  maxfd=readfd3;
  FD_ZERO(&rfds);
  FD_SET(readfd1,&rfds);
  FD_SET(readfd2,&rfds);
  FD_SET(readfd3,&rfds);	
  while(1)
  {
   while(select(maxfd+1,&rfds,NULL,NULL,&tv)<=0){}
   if(FD_ISSET(readfd1,&rfds))
   {
    strcpy(message,"");
    read(readfd1,message,MAX_LEN);
    writefd1=open(FIFO4,O_WRONLY|O_TRUNC);
    writefd2=open(FIFO6,O_WRONLY|O_TRUNC);
    write(writefd1,message,MAX_LEN);
    write(writefd2,message,MAX_LEN);
    close(writefd1);
    close(writefd2);
   }
   else if(FD_ISSET(readfd2,&rfds))
        {
         strcpy(message,"");
         read(readfd2,message,MAX_LEN);
	 writefd1=open(FIFO2,O_WRONLY|O_TRUNC);
	 writefd2=open(FIFO6,O_WRONLY|O_TRUNC);
	 write(writefd1,message,MAX_LEN);
	 write(writefd2,message,MAX_LEN);
	 close(writefd1);
	 close(writefd2);  
        }
        else if(FD_ISSET(readfd3,&rfds))
	     {
	      strcpy(message,"");
	      read(readfd3,message,MAX_LEN);
	      writefd1=open(FIFO2,O_WRONLY|O_TRUNC);
	      writefd2=open(FIFO4,O_WRONLY|O_TRUNC);
	      write(writefd1,message,MAX_LEN);
	      write(writefd2,message,MAX_LEN);
	      close(writefd1);
	      close(writefd2);  
	     }
  }
  close(readfd1);
  close(readfd2);
  close(readfd3);
} 
int main()
{
 int t;
 mkfifo(FIFO1,perm);
 mkfifo(FIFO2,perm);
 mkfifo(FIFO3,perm);
 mkfifo(FIFO4,perm);
 mkfifo(FIFO5,perm);
 mkfifo(FIFO6,perm);
 if(t==-1)
 printf("Error");
 pthread_t t1;
 pthread_create(&t1, NULL, (void*)&c1response, NULL);
 pthread_join(t1, NULL);

}
