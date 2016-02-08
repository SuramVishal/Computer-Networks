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

int main(int argc,char *argv[])
{
	sleep(5);
	kill(atoi(argv[1]),SIGUSR1);
  return 0;
}
