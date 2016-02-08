#include <stdio.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <poll.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void)
{
	mkfifo("redirect",0666);
	struct pollfd pfd[2];
	pfd[0].fd = open("redirect",O_RDWR);
	pfd[0].events = POLLIN;

	while(1)
	{
		while(poll(pfd,3,3000)<=0)
			{printf("inpoll\n");}
		char buf[100];
		read(pfd[0].fd,buf,100);
		printf("%s\n",buf );
	}
}
