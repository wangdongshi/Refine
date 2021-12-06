#include "apue.h"
#include "fcntl.h"

int main(void)
{
	int res;
	char message[] = "Hello FIFO!";

	if (access("./my_fifo", F_OK) == -1) {
		res = mkfifo("./my_fifo", 0644);
		if (res != 0) {
			printf("Create fifo error!\n");
			exit(-1);
		}
	}

	int fifo_fd = open("./my_fifo", O_WRONLY);
	res = write(fifo_fd, message, sizeof(message));
	if (res == -1) {
		printf("Write error on fifo!\n");
		close(fifo_fd);
		exit(-1);
	}
	close(fifo_fd);

	printf("Write success on fifo!\n");
	exit(0);
}
