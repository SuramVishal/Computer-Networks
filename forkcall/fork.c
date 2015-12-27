#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
int main(int argc,char *argv[])
{
 
 int pid=0;
 pid=fork();
 if(pid>0)
 {
    waitpid(pid);
    printf("This is parent:%d \n",getpid());
 }
 else if(pid==0)
 {
    printf("This is child:%d \n",getpid());
 }
 else
 {
    perror("Error forking \n");
 }
 return 0;
}

