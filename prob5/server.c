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
int main(int argc,char *argv[])
{
	int pipefd[2];
	pipe(pipefd);
	int pid = fork();
	if(pid > 0)
	{
		mkfifo("all",0666);
		int fd = open("all",O_RDWR);
		char buf[100];
		struct pollfd pfd[4];
		pfd[0].fd = fd;
		pfd[0].events = POLLIN;
		pfd[1].fd = pipefd[0];
		pfd[1].events = POLLIN;
		close(pipefd[1]);
		printf("hello\n" );
		FILE *fp;
		fp = popen("./pp","r");;
		pfd[2].fd = fileno(fp);
		pfd[2].events = POLLIN;
		make_signal();
		mkfifo("redirect",0666);
		int redir = open("redirect",O_RDWR);
		while(1)
		{
			while(poll(pfd,4,200)<=0)
			{}
			if(pfd[0].revents & POLLIN)
			{	
				read(pfd[0].fd,buf,100);
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
			if(pfd[1].revents & POLLIN)
			{
				char buf2[100];
				read(pfd[1].fd,buf2,100);
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
			if(pfd[2].revents & POLLIN)
			{
				char buf3[100];
				read(pfd[2].fd,buf3,100);
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
