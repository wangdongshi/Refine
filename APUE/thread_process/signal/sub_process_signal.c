#include "apue.h"

static void sig_handler(int signal)
{
	printf("A SIGNAL has been catched by sub process.\n");
}

int main(void)
{
	pid_t pid;

	if (signal(SIGABRT, sig_handler) == SIG_ERR) {
		printf ("Registering SIGNAL handler error!\n");
	}

	pid = getpid();
	printf("---------------------------------\n");
	printf("This is sub process (PID=%lu).\n", (unsigned long)pid);
	printf("---------------------------------\n");

	pause();
	exit(0);
}

