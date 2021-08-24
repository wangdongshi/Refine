#include <stdlib.h>
#include <stdio.h>
#include <sys/utsname.h>

int main()
{
	struct utsname sysInfo;
	int rtn = uname(&sysInfo);
	struct utsname * p = &sysInfo;
	printf("sysname\t: %s\n",	p->sysname);
	printf("nodename\t: %s\n",	p->nodename);
	printf("release\t: %s\n",	p->release);
	printf("version\t: %s\n",	p->version);
	printf("machine\t: %s\n",	p->machine);
	exit(0);
}
