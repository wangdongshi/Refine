#include <sys/stat.h>
#include "apue.h"

int
main (int argc, char *argv[])
{
	struct stat status;
	stat("./testStat.c", &status);
	int mode = status.st_mode;
	int isReg = S_ISREG(mode);
	int isDir = S_ISDIR(mode);
	printf("[mode.isReg]\t: %d\n", isReg);
	printf("[mode.isDir]\t: %d\n", isDir);
	exit(0);
}
