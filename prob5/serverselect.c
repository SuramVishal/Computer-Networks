
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <poll.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include<time.h>
int sigrcv = 0;
void sig_handler(int signo)
{
	printf("received signal\n");
	sigrcv =1;

}
void make_signal()
{
	int a = getpid();
	printf("to send a signal send to my pid %d\n",a);
	signal(SIGUSR1,sig_handler);

}
int getmaxfd(int *fdarr)
{
 int maxfd=fdarr[0];
 if(maxfd<fdarr[1])
 maxfd=fdarr[1];
 if(maxfd<fdarr[2])
 maxfd=fdarr[2];
 return maxfd;
}
int main(int argc,char *argv[])
{
	int pipefd[2];
	pipe(pipefd);
       
	int pid = fork();
	if(pid > 0)
	{
		mkfifo("all",0666);
		int fd = open("all",O_RDONLY);
		char buf[100];
                int fdarr[5];
		struct timeval tv;
                fd_set rfds; 
		FD_SET(fd,&rfds);
                fdarr[0]=fd;
                FD_SET(pipefd[0],&rfds);
		fdarr[1]=pipefd[0];
		close(pipefd[1]);
		FILE *fp;
		fp = popen("./pp","r");;
		FD_SET(fileno(fp),&rfds);
		fdarr[2]=fileno(fp);
                printf("y");
		make_signal();
                printf("y");
                int t;
		mkfifo("redirect",0666);
                if(t==-1)
                perror("error");
		int redir = open("redirect",O_WRONLY);
                int maxfd=getmaxfd(fdarr);
                tv.tv_sec=1;
                tv.tv_usec=0;
                printf("Hello");
		while(1)
		{
		       while(select(maxfd+1,&rfds,NULL,NULL,&tv)<=0)
                       {}
			if(FD_ISSET(fdarr[0],&rfds))
			{	
				read(fdarr[0],buf,100);
				if(sigrcv==1)
				{
					printf("sig1\n");	
					write(redir,buf,strlen(buf));
				}
				else
				{
					printf("sig bot 1");
					printf("%s\n",buf);
				}
			}
			if(FD_ISSET(fdarr[1],&rfds))
			{
				char buf2[100];
				read(fdarr[1],buf2,100);
				if(sigrcv==1)
				{
					printf("sig2\n");
					write(redir,buf2,strlen(buf2));
				}
				else
				{
					printf("sig2 not 1\n");
					printf("%s\n",buf2);
				}
			}
			if(FD_ISSET(fdarr[2],&rfds))
			{
				char buf3[100];
				read(fdarr[2],buf3,100);
				if(sigrcv==1)
				{
					printf("sig3\n");
					write(redir,buf3,strlen(buf3));
				}
				else
				{
					printf("sig3 not 1\n");
					printf("%s\n",buf3);	
				}
			}
                       
		} 
	}
	else
	{
		while(1)
		{
			sleep(3);
			close(pipefd[0]);
			char buf[] = "from pipe";
			write(pipefd[1],buf,strlen(buf));
		}
	}
}
