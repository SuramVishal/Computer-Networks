#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#define FIFO "filie"
#define perm 0666
#define MAX_LEN 20
int main()
{
  char msgrcv[MAX_LEN]="";
  char msgsnd[MAX_LEN]="";
  if((mkfifo(FIFO,perm)<0)&&(errno!=EEXIST))   //checking for success of creation,but mkfifo returns error if the file already exists,apart 
  {                                           //from that if ther's any other problem in make fifo ,we will be notified(EEXIST can be ignored)
   printf("Could not create a fifo\n");
  }
  pid_t pid=fork();
  if(pid==0)
  {                                          
  int fd=open(FIFO,O_WRONLY|O_APPEND);   //a fifo is only way, it cant be both read and write,for the reason we write in child and read parent
  printf("Enter the message for server\n");  
  fgets(msgsnd,MAX_LEN,stdin);
  msgsnd[strlen(msgsnd)-1]='\0'; //Nulling out the newline char in the input****
  write(fd,msgsnd,MAX_LEN);
  printf("Client:%s\n",msgsnd);
  close(fd);                   //closing the fd
  }
  else if(pid>0)
  {
  int fd=open(FIFO,O_RDONLY);  
  read(fd,msgrcv,MAX_LEN);
  printf("Server:Received Message-\"%s\"\n",msgrcv);
  close(fd);               
  unlink(FIFO);                //deleting the fifo
  }
  return 0;
}

