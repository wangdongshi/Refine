#include "apue.h"

int main(void)
{
	pid_t pid;

	pid = getpid();
	printf("---------------------------------\n");
	printf("This is sub process (PID=%lu).\n", (unsigned long)pid);
	printf("---------------------------------\n");

	exit(0);
}

