#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>

int 
main(void)
{
	char buf[64];
	time_t t;
	struct tm *pTime;

	t = INT_MAX;
	pTime = gmtime(&t);
	strftime(buf, 64, "%c", pTime);
	printf("%s\n", buf);

	exit(0);
}
