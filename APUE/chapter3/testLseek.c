#include "apue.h"
#include <fcntl.h>

char buf[] = "abcdefghijklmnopqrstuvwxyz\n";
char res[600];

int 
main(void)
{
	int fd;
	// make a test file
	if ((fd = open("./testSeek.txt", O_CREAT | O_RDWR)) < 0) {
		printf("create file error!\n");
		exit(-1);
	}
	if (write(fd, buf, 27) != 27) {
		printf("write file error!\n");
		exit(-1);
	}
	close(fd);
	
	// open this file with O_APPEND | O_WRONLY and test lseek
	if ((fd = open("./testSeek.txt", O_WRONLY | O_APPEND)) < 0) {
		printf("open file error!\n");
		exit(-1);
	}
	if (lseek(fd, 2, SEEK_SET) == -1) {
		printf("lseek error\n");
		exit(-1);
	}
	if (write(fd, buf, 27) != 27) {
		printf("write file error in second time!\n");
		exit(-1);
	}
	close(fd);

	// open this file with O_APPEND | O_RDONLY and test lseek
	if ((fd = open("./testSeek.txt", O_RDONLY | O_APPEND)) < 0) {
		printf("open file error!\n");
		exit(-1);
	}
	if (lseek(fd, 2, SEEK_SET) == -1) {
		printf("lseek error\n");
		exit(-1);
	}
	if (read(fd, res, 27) != 27) {
		printf("read file error in second time!\n");
		exit(-1);
	} else {
		printf("The reading result is \"%s\"\n", res);
	}
	close(fd);

	exit(0);
}
