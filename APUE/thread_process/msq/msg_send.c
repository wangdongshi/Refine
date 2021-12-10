#include "apue.h"
#include "sys/ipc.h"
#include "sys/msg.h"
#include "errno.h" 

typedef struct msgbuf
{
	long mtype;
	char mdata[100];
} msg_t;

int main(void)
{
	msg_t msg;
	
	int msgid = msgget((key_t)1234, IPC_EXCL);
	if (msgid == -1) {
		msgid = msgget((key_t)1234, IPC_CREAT);
		if (msgid == -1) {
			printf("Create message queue error!\n");
			exit(-1);
		}
	}
	
	msg.mtype = 1;
	strcpy(msg.mdata, "Test message.");

	while (1) {
		int res = msgsnd(msgid, (void*)&msg, 100, 0);
		if (res < 0) {
			printf("Send message error. ERROR_NO=%d[%s]\n", errno, strerror(errno));
			exit(-1);
		}
		printf("Send a message '%s'.\n", msg.mdata);
		sleep(3);
	}
	
	msgctl(msgid, IPC_RMID, 0);

	exit(0);
}
