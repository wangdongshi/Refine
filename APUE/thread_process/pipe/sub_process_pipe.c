#include "apue.h"

int main(int argc, char* argv[])
{
	pid_t pid;

	pid = getpid();
	printf("---------------------------------\n");
	printf("This is sub process (PID=%lu).\n", (unsigned long)pid);
	printf("---------------------------------\n");
	
	//printf("Sub process get arg0='%s', arg1='%d', arg2='%d'.\n", argv[0], *argv[1], *argv[2]);
	
	int fd[2] = {*argv[1], *argv[2]};
	close(fd[0]);
	write(fd[1], "Hello pipe!", 12);
	close(fd[1]);

	exit(0);
}

