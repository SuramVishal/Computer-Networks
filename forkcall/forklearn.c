#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
int main()
{
 int i=2;
 pid_t pid=fork();
 if(pid>0)
 {
  wait(); 
  int status;
  printf("parent");
  waitpid(0,&status,0); //waits till the child process of same group terminates   
  waitpid(-1,&status,0); //waits till the child process of any group terminates
  //waitpid(3,&status,0); //waits till the cild process with id 3     
 }
 else if(pid==0)              //usually child process executes first,the logic is if child runs first then the overhead of copy on write is 
     {                         //eliminated,if the child process is calling exec,because the parent can't write to the adrress space if copy on                                 write is not done.
        printf("child");
     }
}
