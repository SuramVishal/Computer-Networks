#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<pthread.h>
#define FIFO1 "server_to_client1"
#define FIFO2 "client_to_server1"
#define FIFO3 "client_to_server2"
#define FIFO4 "server_to_client2"
#define FIFO5 "client_to_server3"
#define FIFO6 "server_to_client3"
#define perm 0666
#define MAX_LEN 20

 char message[MAX_LEN]="";
 int i,n,readfd,writefd1,writefd2;
void c1response()
{
 while(1)
  {
   readfd=open(FIFO2,O_RDONLY);
   strcpy(message,"");
   read(readfd,message,MAX_LEN);
   writefd1=open(FIFO4,O_WRONLY);
   writefd2=open(FIFO6,O_WRONLY);
   write(writefd1,message,MAX_LEN);
   write(writefd2,message,MAX_LEN);
   close(readfd);
   close(writefd1);
   close(writefd2);
    
   }
}
void c2response()
{
 while(1)
  {
   readfd=open(FIFO3,O_RDONLY);
   strcpy(message,"");
   read(readfd,message,MAX_LEN);
   writefd1=open(FIFO1,O_WRONLY);
   writefd2=open(FIFO6,O_WRONLY);
   write(writefd1,message,MAX_LEN);
   write(writefd2,message,MAX_LEN);
   close(readfd);
   close(writefd1);
   close(writefd2);
    
   }
}
void c3response()
{
 while(1)
  {
   readfd=open(FIFO5,O_RDONLY);
   strcpy(message,"");
   read(readfd,message,MAX_LEN);
   writefd1=open(FIFO1,O_WRONLY);
   writefd2=open(FIFO4,O_WRONLY);
   write(writefd1,message,MAX_LEN);
   write(writefd2,message,MAX_LEN);
   close(readfd);
   close(writefd1);
   close(writefd2);
    
   }
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
 pthread_t t1,t2,t3;
 pthread_create(&t1, NULL, (void*)&c1response, NULL);
 pthread_create(&t2, NULL, (void*)&c2response, NULL);
 pthread_create(&t3, NULL, (void*)&c3response, NULL);
 pthread_join(t1, NULL);
 pthread_join(t2, NULL);
 pthread_join(t3, NULL);
}
