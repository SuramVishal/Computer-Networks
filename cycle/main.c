#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/types.h>
#include<signal.h>
#include<sys/ipc.h>
#include<fcntl.h>
#include<string.h>
#define buffersize 20
int main(int argc,char *argv[])
{
 char buffer[buffersize];
 printf("Enter input\n");
 fgets(buffer,buffersize,stdin);
 FILE *to_p;
 FILE *from_p;
 printf("Yo");
 int i=1;
 printf("Yo");
 char p[buffersize];
 strcpy(p,"./");
 int pipes[2];
 pipe(pipes);
  //for(i=1;i<argc;i++)
  //{
  //from_p=popen(argv[i],"r");
  //int pid=fork();
  //if(pid>0)
  //{
   int copy;
   dup2(1,copy);
   dup2(pipes[1],1);
   strcat(p,argv[i]);
   to_p=popen(p,"w");
   fputs(buffer,to_p);
   read(pipes[0],buffer,buffersize);
   dup2(copy,1);
   printf("Input: %s",buffer);
  //}
 // fgets(buffer,buffersize,from_p);
 // printf("Process %d : %s/n",i,buffer);
 // pclose(from_p);
  pclose(to_p);
 //}
}
