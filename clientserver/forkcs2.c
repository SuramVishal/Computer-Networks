#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#define MAX_LEN 20
int main()
{
 char msgsnd[MAX_LEN]="";
 char msgrcv[MAX_LEN]="";
 int fd[2];
 pipe(fd);
 pid_t pid=fork();
 if(pid==0)
 { 
  close(fd[0]);
  printf("Enter the message to be sent to server\n");
  //scanf("%[^\n]%*s",msgsnd);      // to take input separated by newline rather than space which is default
  fgets(msgsnd,MAX_LEN,stdin);      //works better with no complexities
  int error= write(fd[1],msgsnd,strlen(msgsnd));
  if(error<=0)
  printf("Error writing or no input");
 }
 else if(pid>0)
 {
  wait();    //wait for the child to write the string in the pipe and terminate,but usually child is given a priority to execute
  close(fd[1]);
  int error= read(fd[0],msgrcv,MAX_LEN);
  if(error<=0)
  printf("Error Reading or nothing read");
  else
  printf("Message received is: %s\n",msgrcv);
 }
 
}
