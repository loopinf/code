#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>


#define POSIX_MQ_NAME		"/posixmsgq"
#define MSGBUF_STR_SIZE		8192

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
	mqd_t mqd;
	struct mq_attr attr;

	mqd = mq_open(POSIX_MQ_NAME, O_RDWR | O_CREAT, 0644, NULL);
	if (mqd == -1) {
		perror("mq_open()");
		return -1;
	}
	memset(&attr, 0, sizeof(attr));
	if (mq_getattr(mqd, &attr) == -1) {
		close(mqd);
		return -1;
	}
  
  printf("mq_flags   = %ld\n", attr.mq_flags);
  printf("mq_maxmsg  = %ld\n", attr.mq_maxmsg);
  printf("mq_msgsize = %ld\n", attr.mq_msgsize);
  printf("mq_curmsgs = %ld\n", attr.mq_curmsgs);

	return mqd;
}

static int send(char* string, unsigned int priority)
{
  int mqd;
	char buf[MSGBUF_STR_SIZE];

	mqd = init_msgq();
	if (mqd == -1) {
		perror("init_msgq()");
		return -1;
	}

	memset(buf, 0, sizeof(buf));  
  snprintf(buf, sizeof(buf),"pid %d: %s", getpid(), string);
  printf("send data: %s\n", buf);
	if (mq_send(mqd, buf, sizeof(buf), priority) == -1) {
		perror("mq_send()");
		close(mqd);
		return -1;
	}

	return 0;
}

static int recv()
{
	int mqd;
	char buf[MSGBUF_STR_SIZE];
	unsigned priority;

	mqd = init_msgq();
	if (mqd == -1) {
		perror("init_msgq()");
		return -1;
	}

	memset(buf, 0, sizeof(buf));
	if (mq_receive(mqd, buf, sizeof(buf), &priority) == -1) {
		perror("mq_receive()");
		close(mqd);
		return -1;
	}
	printf("prio %u, msg [%s]\n", priority, buf);

	return 0;
}

int main(int argc, char **argv)
{
	int ret;
	unsigned int pri;

  // 사용법: ./4.posixmsgq.c send priority string
	if (argc < 2) {
	  printf("%s send priority string\n", argv[0]);
		return -1;
	}

	if (!strcmp(argv[1], "send")) {
	  pri = (unsigned int)strtol(argv[2], NULL, 10);
		ret = send(argv[3], pri);
	} else if (!strcmp(argv[1], "recv")) {
		ret = recv();
	} else {
    perror("command error");
    return -1;
	}

	return ret;
}