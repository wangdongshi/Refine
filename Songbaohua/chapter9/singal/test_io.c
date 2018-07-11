#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

#define MAX_LEN     100

void sig_handler(int sig)
{
    char data[MAX_LEN];
    int len;

    len = read(STDIN_FILENO, &data, MAX_LEN);
    data[len] = 0;
    printf("input available:%s\n", data);
}

int main(void)
{
    int oflags;

    signal(SIGIO,  sig_handler);
    fcntl(STDIN_FILENO, F_SETOWN, getpid());
    oflags = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, oflags | FASYNC);
    
    while(1);

    return 0;
}

