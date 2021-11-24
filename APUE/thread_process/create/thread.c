#include "apue.h"
#include <pthread.h>

static void printids(void)
{
	pid_t		pid;
	pthread_t	tid;

	pid = getpid();
	tid = pthread_self();
	printf("PID=%lu, TID=0x%lx.\n", (unsigned long)pid, (unsigned long)tid);
}

void* thread1_fun(void* arg)
{	
	printf("----------------------------\n");
	printf("This is new thread.\n");
	printids();
	printf("----------------------------\n");
}

int main(void)
{
	pthread_t thread_id;
	int err;
	int arg = 13; // thread function parameter
	err = pthread_create(&thread_id, NULL, thread1_fun, &arg);
	printf("----------------------------\n");
	printf("This is main thread.\n");
	printids();
	printf("----------------------------\n");
	sleep(1);
	exit(0);
}
