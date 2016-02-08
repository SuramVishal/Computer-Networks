#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/types.h>
#include<signal.h>
#include<sys/ipc.h>
#include<fcntl.h>
#define buffersize 20
int main()
{
 char buffer[20];
 scanf("%s",buffer);
 printf("%s",buffer);
 
}
	
