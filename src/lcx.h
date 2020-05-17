// lcx.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#ifndef LCX_H /* only run through this once */
#define LCX_H

//ss#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <netdb.h>

#include <getopt.h>
#include "LcxConfig.h"

#define TIMEOUT 300
#define MAXSIZE 20480
#define HOSTLEN 40
#define CONNECTNUM 5

//The following macro increased to modify,but i can't ensure they are correct. by:三只小潴
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
typedef unsigned int UINT;
//------------------------------------------------------------------------------------//

// define 2 socket struct
struct transocket
{
	int fd1;
	int fd2;
};

typedef enum _METHOD
{
	LISTEN = 1,
	TRAN,
	SLAVE,
	SSOCKSD,
	RCSOCKS,
	RSSOCKS,
	NETCAT
} METHOD;

#define STR_LISTEN "listen"
#define STR_TRAN "tran"
#define STR_SLAVE "slave"
#define STR_SSOCKSD "ssocksd"
#define STR_RCSOCKS "rcsocks"
#define STR_RSSOCKS "rssocks"
#define STR_NETCAT "netcat"

typedef struct _GlobalArgs
{
	METHOD method;		 /* -methon option */
	char *logFileName; /* -o option */
	FILE *logFile;
	int verbosity; /* -v option */

	int iListenPort;
	char *listenHost;

	int iConnectPort;
	char *connectHost;

	int iTransmitPort;
	char *transmitHost;

	int bFreeConsole;

	int ssl;
} GlobalArgs;

// define function
void ver();
void usage(char *prog);
void transmitdata(void *data);
void getctrlc(int j);
void closeallfd();
void makelog(char *buffer, unsigned long length);

void bind2bind(GlobalArgs args);
void bind2conn(GlobalArgs args);
void conn2conn(GlobalArgs args);
int testifisvalue(char *str);
int create_socket();
int create_server(int sockfd, int port);
int client_connect(int sockfd, char *server, int port);

METHOD str2method(char *method);

void ssocksd(GlobalArgs args);
void rcsocks(GlobalArgs args);
void rssocks(GlobalArgs args);
void netcat(int argc, char **argv);

/* ================ */
#endif /* LCX_H */
