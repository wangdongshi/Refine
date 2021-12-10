#include "apue.h"
#include "sys/msg.h"

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
	while (1) {
		int res = msgrcv(msgid, &msg, 100, msg.mtype, 0);
		if (res >= 0) {
			printf("Message = '%s'.\n", msg.mdata);
		}
	}

	exit(0);
}
