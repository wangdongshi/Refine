#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

#define MAX_LEN     100

void sig_handler(int sig)
{
    printf("receive a signal from globalfifo, signal:%d\n", sig);
}

int main(void)
{
    int fd, oflags;

    fd = open("/dev/globalfifo", O_RDWR, S_IRUSR | S_IWUSR);
    if (fd != -1) {
        signal(SIGIO,  sig_handler);
        fcntl(fd, F_SETOWN, getpid());
        oflags = fcntl(fd, F_GETFL);
        fcntl(fd, F_SETFL, oflags | FASYNC);
    
        while(1) {
            sleep(100);
        }
    } else {
        printf("device open failure\n");
    }

    return 0;
}

