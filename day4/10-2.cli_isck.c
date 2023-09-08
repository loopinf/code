#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define DEFAULT_PROTOCOL 0
#define MAXLINE 100

int readLine(int fd, char* str)
{
  int n;
  do {
    n = read(fd, str, 1);
  } while(n > 0 && *str++ != 0x00);
  return(n > 0);

}
/* 파일 클라이언트 */
int main (int argc, char* argv[])
{
  int clientFd, port, result;
  char *host, inmsg[MAXLINE], outmsg[MAXLINE];
  struct sockaddr_in serverAddr;
  struct hostent *hp;
  if (argc != 3) {
    fprintf(stderr, "사용법 : %s <host> <port>\n", argv[0]);
    exit(0);
  }

  host = argv[1];
  port = atoi(argv[2]);
  clientFd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);

  /* 접속지 서버 IP 주소와 포트 정보 할당 */
  if ((hp = gethostbyname(host)) == NULL) {
    perror("gethostbyname error"); // 호스트 찾기 오류
  }
  bzero((char *) &serverAddr, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  bcopy((char *)hp->h_addr_list[0], (char *)&serverAddr.sin_addr.s_addr, hp->h_length);
  serverAddr.sin_port = htons(port);
  do { /* 연결 요청 */
    result = connect(clientFd, (const struct sockaddr*)&serverAddr,  sizeof(serverAddr));
    if (result == -1) { 
      sleep(1);
    }
  } while (result == -1);


  printf("파일 이름 입력:");
  scanf("%s", inmsg);
  write(clientFd,inmsg,strlen(inmsg)+1);

  /* 소켓으로부터 파일 내용 읽어서 프린트 */
  while (readLine(clientFd,outmsg)) {
    printf("%s", outmsg);
  }
  close(clientFd);
  exit(0);
}

// gethostent