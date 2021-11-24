#include "apue.h"

int main(void)
{
	pid_t pid;

	pid = getpid();
	printf("---------------------------------\n");
	printf("This is main process (PID=%lu).\n", (unsigned long)pid);
	printf("---------------------------------\n");

	pid = fork();

	if (pid < 0) {
		printf("Fork error!\n");
	}
	else if (pid == 0) {
		int arg = 13;
		int result = execl("./sub_process_signal.out", "sub_process_signal.out", NULL);
		if (result < 0) {
			printf("./sub_process_signal.out does not exist!\n");
		}
	}
	
	sleep(1);

	int result = kill(pid, SIGABRT);
	if (result == 0) {
		printf("A SIGNAL has been send from main process.\n");
	}
	else {
		printf("SIGNAL sending error!\n");
	}

	sleep(1);
	exit(0);
}
