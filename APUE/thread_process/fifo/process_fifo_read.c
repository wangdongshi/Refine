#include "apue.h"
#include "fcntl.h"

int main(void)
{
	int res;
	char buf[100];
	int fifo_fd = open("./my_fifo", O_RDONLY);

	do {
		res = read(fifo_fd, buf, sizeof(buf)); 
	} while (res > 0);
	close(fifo_fd);
	
	printf("Message from fifo is '%s'\n", buf);
	exit(0);
}

