#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/types.h>
#include<signal.h>
#include<sys/ipc.h>
#define size 4
int err,i;
int *x,*y;
int p2pid;
union semun
{
 int val;
 short *array;
 struct semid_ds *buf;
 struct seminfo *_buf;
};
void semacq(int semid,int semnum)
{
 struct sembuf temp;
 temp.sem_num=semnum;
 temp.sem_op=-1;
 temp.sem_flg=0;
 int error=semop(semid,&temp,1);
 if(error==-1)
 {
  printf("Sem Op Error");
  exit(1);
 }
}
void semrel(int semid,int semnum)
{
 struct sembuf temp;
 temp.sem_num=semnum;
 temp.sem_op=1;
 temp.sem_flg=0;
 int error=semop(semid,&temp,1);
 if(error==-1)
 {
  printf("Sem Op Error");
  exit(1);
 }
}
void handler()
{
 *x=*y+1;
 printf("X=%i",*x);
 signal(SIGUSR1,handler);
 if(*y<100)
 {
  kill(p2pid,SIGUSR1);
 }
}
int main()
{
 key_t key1=2234;
 key_t key2=2235;
 key_t key3=2236;
 int semid=semget(key1,2,IPC_CREAT|0666);
 if(semid==-1)
 {
  printf("Error getting semaphores");
  exit(1);
 }
 for(i=0;i<2;i++)
 {
  union semun tmp; 
  tmp.val=0;
  semctl(semid,i,SETVAL,tmp);
 }
 int shmid1=shmget(key2,size,IPC_CREAT|0666);
 int shmid2=shmget(key3,size,IPC_CREAT|0666);
 if(shmid1==-1||shmid2==-1)
 { 
  printf("Error getting shared memory");
  exit(1);
 }
 x=shmat(shmid1,NULL,0);
 y=shmat(shmid2,NULL,0);
 signal(SIGUSR1,handler);
 *x=getpid();
 semrel(semid,1);
 semacq(semid,0);
 p2pid=*y;
 *y=0;
 while(*y<100){}
}
