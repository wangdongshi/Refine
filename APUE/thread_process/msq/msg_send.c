#include "apue.h"
#include "sys/ipc.h"
#include "sys/msg.h"

typedef struct msgbuf
{
	long mtype;
	char mdata[100];
} msg_t;

int main(void)
{
	msg_t msg;
	key_t key = ftok("./my_msq", 0);
	printf("Message queue key = [%x]\n", key);

	int msgid = msgget(key, IPC_CREAT);
	if (msgid == -1) {
		printf("Create message queue error!\n");
		exit(-1);
	}
	
	msg.mtype = getpid();
	strcpy(msg.mdata, "Test message.");

	while (1) {
		int res = msgsnd(msgid, &msg, sizeof(msg), 0);
		if (res == -1) {
			printf("Send message error!\n");
			exit(-1);
		}
		sleep(1);
	}

	exit(0);
}
