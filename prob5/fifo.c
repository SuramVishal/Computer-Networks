#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>
int main()
{
	mkfifo("all",0666);
	int fd = open("all",O_RDWR);
	char buf[100];
	
	
	int k = 0;
	while(1)
	{
		scanf("%s",buf);
		write(fd,buf,strlen(buf));
	}
	
}
