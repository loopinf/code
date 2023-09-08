#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgdata {
  int value;  
	char string[128];
};

struct msgbuf {
	long mtype;
  struct msgdata body;
};

static int init_msgq(void)
{
	int msgq;
	key_t key;
	key = 5578;

	msgq = msgget(key, 0644 | IPC_CREAT);
	if (msgq == -1) {
		perror("msgget()");
		return -1;
	}

	return msgq;
}

static int send(long mtype, char* value, char* string)
{
	int msgq;
	struct msgbuf mbuf;

	msgq = init_msgq();
	if (msgq == -1) {
		perror("init_msgq()");
		return -1;
	}

	memset(&mbuf, 0, sizeof(mbuf));
	mbuf.mtype = mtype;

	mbuf.body.value = strtol(value, NULL, 10);      
	snprintf(mbuf.body.string, sizeof(mbuf.body.string), "%s", string);
	printf("send=>mtype:%ld, value:%d, string:%s\n", mtype, mbuf.body.value, string);

	if (msgsnd(msgq, &mbuf, sizeof(mbuf.body), 0) == -1) {
		perror("msgsnd()");
		return -1;
	}

	return 0;
}

static int recv(long mtype)
{
	int msgq;
	struct msgbuf mbuf;
	int ret;

	msgq = init_msgq();
	if (msgq == -1) {
		perror("init_msgq()");
		return -1;
	}

	memset(&mbuf, 0, sizeof(mbuf));
	ret = msgrcv(msgq, &mbuf, sizeof(mbuf.body), mtype, 0);
	if (ret == -1) {
		perror("msgrcv()");
		return -1;
	}
	printf("recved msg: mtype %ld, msg [%d, %s]\n",
			    mbuf.mtype, mbuf.body.value, mbuf.body.string);

	return 0;
}

int main(int argc, char **argv)
{
	int ret;
	long mtype;

  // 사용법: ./3.sysvmsgq.c send msgtype numvalue strvalue
	if (argc < 3) {
	  printf("%s send msgtype numvalue strvalue\n", argv[0]);
		return -1;
	}

	mtype = strtol(argv[2], NULL, 10);

	if (!strcmp(argv[1], "send")) {
		if (mtype <= 0) {
      perror("mtype <=0");
			return -1;
		}
		ret = send(mtype, argv[3], argv[4]);
	} else if (!strcmp(argv[1], "recv")) {
		ret = recv(mtype);
	} else {
    perror("command error");
    return -1;
	}

	return ret;
}