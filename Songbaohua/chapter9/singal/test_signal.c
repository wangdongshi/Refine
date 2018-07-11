#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int sig)
{
    printf("Caught the signal No. %d\n", sig);
}

int main(void)
{
    signal(SIGINT,  sig_handler);
    signal(SIGTERM, sig_handler);
    while(1);

    return 0;
}

