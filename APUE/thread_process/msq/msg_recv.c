#include "apue.h"
#include "sys/msg.h"

int main(void)
{
	key_t key = ftok("./my_msq", 0);
	printf("Message queue key = [%x]\n", key);

	int msgid = msgget(key, 0);
	if (msgid == -1) {
		printf("Get message key error!\n");
		exit(-1);
	}
	
	while (1) {
		char buf[100] = {};
		long msg_type = 0;
		int  r_cnt_flag = 0;
		int res = msgrcv(msgid, buf, sizeof(buf), msg_type, r_cnt_flag);
		if (!res) {
			printf("Message = '%s'.\n", buf);
		}
	}

	exit(0);
}
