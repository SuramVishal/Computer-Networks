#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#define MSG_LEN 20
int main()
{
 int fd[2];
 int error=pipe(fd);
 if(error<0)
 {
  printf("error while creating a pipe");
 }
 char *message="Hello this is client";
 pid_t pid=fork();
 if(pid==0)
 {
  error=write(fd[1],message,strlen(message));
  if(error<0)
  printf("error writing\n");
 }
 else if(pid>0)
      {
        wait();
        char rcv[MSG_LEN];
        read(fd[0],rcv,MSG_LEN);
        printf("Hello this is server\nReceived your message:%s\n",rcv);
      }

}
