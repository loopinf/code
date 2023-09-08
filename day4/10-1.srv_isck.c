#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
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
/* 파일 서버 */
int main (int argc, char* argv[])
{
  int listenfd, connfd, port;
  unsigned int clientlen;
  FILE *fp;
  char inmsg[MAXLINE], outmsg[MAXLINE];
  struct sockaddr_in serveraddr, clientaddr;
  char *ipaddr;
  signal(SIGCHLD, SIG_IGN);

  if (argc != 2) {
    fprintf(stderr, "사용법: %s <port>\n", argv[0]);
    exit(0);
  }
  port = atoi(argv[1]);

  listenfd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);

  //bzero((char *) &serveraddr, sizeof(serveraddr));
  memset(&serveraddr, 0x00, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons((unsigned short)port);
  bind(listenfd, (const struct sockaddr*)&serveraddr, sizeof(serveraddr));
  listen(listenfd, 5);
  while (1) {
    clientlen = sizeof(clientaddr);
    connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen); 

    /* 클라이언트 정보 가져오기 */
    gethostbyaddr((char *)&clientaddr.sin_addr.s_addr, sizeof(clientaddr.sin_addr.s_addr), AF_INET);
    ipaddr = inet_ntoa(clientaddr.sin_addr);
    printf("서버: (%s) %d에 연결됨\n", ipaddr, clientaddr.sin_port);

    if (fork() == 0) {
      readLine(connfd, inmsg);
      fp = fopen(inmsg, "r");  
      if (fp == NULL) {
        write(connfd, "not found file\n", 15);
      } else { 
        while(fgets(outmsg, MAXLINE, fp) != NULL) {
          write(connfd, outmsg, strlen(outmsg)+1);
        }
      }
      close(connfd);
      exit (0);
    } 
    else { 
      close(connfd);
    }
  }  // while
}  // main

