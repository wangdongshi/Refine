#include "apue.h"
#include <errno.h>
#include <limits.h>

#define CONF	_SC_ARG_MAX

int main(int argc, char *argv[])
{
	printf("_SC_ARG_MAX = 0x%08lx\n", sysconf(CONF));
}
