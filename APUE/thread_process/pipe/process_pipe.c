#include "apue.h"

int main(void)
{
	pid_t pid;

	pid = getpid();
	printf("---------------------------------\n");
	printf("This is main process (PID=%lu).\n", (unsigned long)pid);
	printf("---------------------------------\n");

	int fd[2];
	if (pipe(fd) == -1) {
		printf("Pipe creating error!\n");
	}

	pid = fork();

	if (pid < 0) {
		printf("Fork error!\n");
	}
	else if (pid == 0) {
		int arg = 13;
		char argv[2] = {fd[0], fd[1]};
		int result = execl("./sub_process_pipe.out", "sub_process_pipe.out", &argv[0], &argv[1], NULL);
		if (result < 0) {
			printf("./sub_process_pipe.out does not exist!\n");
		}
	}
	
	sleep(1);
	
	close(fd[1]);
	char buf[100] = {0};
	read(fd[0], buf, 30);
	printf("main process received message \"%s\" from PIPE.\n", buf);
	close(fd[0]);
	
	sleep(1);
	exit(0);
}
