#include<stdio.h>         //to work,the program to be executed using execve must be binary executable code for which one should compile the 
#include<stdlib.h>        //prior to using this code,commands =>  "gcc execute.c -o execute" "gcc test.c -o test" "./execute ./test 
int main(int argc,char *argv[])
{
 int pid=0;
 pid=fork();
 if(pid>0)
 {
   printf("Parent Executing with process id:%d\n",getpid());
   waitpid(pid,0,0);       //waiting for the child process to end
 }
 else if(pid==0)
 { 
   printf("Child Executing with process id:%d\n",getpid());
   printf("Executing %s\n",argv[1]);
   char *toexecute=argv[1];
   char *newarg[argc];      //new arguments for the program to be executed
   char *newenviron[]={NULL};
   int i;
   for(i=0;i<argc;i++)
   {
    newarg[i]=argv[i];      //teaking in the arguments into a separate array
   }
   newarg[argc]=NULL;
   execve(argv[1],newarg,newenviron);    //program jumps to the new program ignoring the post-code
   printf("execve did not work");
 }
 return 0;
}
