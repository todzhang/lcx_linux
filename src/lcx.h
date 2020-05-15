// lcx.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#ifndef LCX_H		/* only run through this once */
#define LCX_H

//ss#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <signal.h>
#include  <netinet/in.h>
#include  <arpa/inet.h>
#include <pthread.h>
#include <netdb.h>


#define VERSION                        "1.00"
#define TIMEOUT                        300
#define MAXSIZE                        20480
#define HOSTLEN                        40
#define CONNECTNUM                     5

//The following macro increased to modify,but i can't ensure they are correct. by:三只小潴
#define INVALID_SOCKET                 -1
#define SOCKET_ERROR                   -1
typedef unsigned int UINT;
//------------------------------------------------------------------------------------//

// define 2 socket struct
struct transocket
{
    int fd1;
    int fd2;
};

// define function
void ver();
void usage(char *prog);
void transmitdata(void *data);
void getctrlc(int j);
void closeallfd();
void makelog(char *buffer, unsigned long length);
void bind2bind(int port1, int port2);
void bind2conn(int port1, char *host, int port2);
void conn2conn(char *host1, int port1, char *host2, int port2);
int testifisvalue(char *str);
int create_socket();
int create_server(int sockfd, int port);
int client_connect(int sockfd, char* server, int port);

/* ================ */
#endif /* LCX_H */
