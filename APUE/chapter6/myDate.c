#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int
main(void)
{
	time_t t = time(NULL);
	printf("UTC = %d\n", (int)t);
	char buf[64];

	struct tm * pTime = localtime(&t);
	strftime(buf, 64, "%F %a %X %Z", pTime);
	printf("%s\n", buf);
	exit(0);
}
