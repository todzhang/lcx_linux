
#include "lcx.h"

/* helpme :
	  the obvious */
static int helpme()
{
  printf("lcx v" VERSION "\n");
  printf("./lcx ([-options][values])* \n\
	options :\n\
	- S state setup the function.You can pick one from the following options :\n\
	ssocksd, rcsocks, rssocks, listen, tran, slave, netcat\n\
	- l listenport open a port for the service startup.\n\
	- d refhost set the reflection host address.\n\
	- e refport set the reflection port.\n\
	- f connhost set the connect host address .\n\
	- g connport set the connect port.\n\
	- h help show the help text, By adding the - s parameter, you can also see the more detailed help.\n\
	- a about show the about pages\n\
	- v version show the version.\n\
	- t usectime set the milliseconds for timeout.The default value is 1000");
  return (0);
} /* helpme */

METHOD str2method(char *method)
{
  if (!strcmp(method, STR_LISTEN))
  {
    return LISTEN;
  }
  else if (!strcmp(method, STR_TRAN))
  {
    return TRAN;
  }
  else if (!strcmp(method, STR_SLAVE))
  {
    return SLAVE;
  }
  else if (!strcmp(method, STR_SSOCKSD))
  {
    return SSOCKSD;
  }
  else if (!strcmp(method, STR_RCSOCKS))
  {
    return RCSOCKS;
  }
  else if (!strcmp(method, STR_RSSOCKS))
  {
    return RSSOCKS;
  }
  else if (!strcmp(method, STR_NETCAT))
  {
    return NETCAT;
  }
  else
  {
    return 0;
  }
}

GlobalArgs globalArgs;

//***************s*********************************************************************
//
// function main
//
//************************************************************************************
int main(int argc, char *argv[])
{
  /* Initialize globalArgs before we get to work. */
  memset(&globalArgs, 0, sizeof(globalArgs));

  register int option;
  while ((option = getopt(argc, argv, ":S:l:m:d:e:f:g:v:")) != EOF)
  {

    switch (option)
    {
    case 'S':
      printf("Given Option: %c\n", option);
      if (optarg)
      {
        globalArgs.method = str2method(optarg);
      }
      if (globalArgs.method == NETCAT)
      {
        goto argsFinished;
      }
      break;

    case 'l':
      printf("Given Option: %c\n", option);
      if (optarg)
      {
        globalArgs.iListenPort = atoi(optarg);
      }
      break;

    case 'm':
      printf("Given Option: %c\n", option);
      if (optarg)
      {
        globalArgs.iTransmitPort = atoi(optarg);
      }
      break;

    case 'd':
      printf("Given Option: %c\n", option);
      if (optarg)
      {
        globalArgs.connectHost = optarg;
      }
      break;

    case 'e':
      printf("Given Option: %c\n", option);
      if (optarg)
      {
        globalArgs.iConnectPort = atoi(optarg);
      }
      break;

    case 'f':
      printf("Given Option: %c\n", option);
      if (optarg)
      {
        globalArgs.transmitHost = optarg;
      }
      break;

    case 'g':
      printf("Given Option: %c\n", option);
      if (optarg)
      {
        globalArgs.iTransmitPort = atoi(optarg);
      }
      break;

    case 'v':
      printf("Given Option: %c\n", option);
      globalArgs.verbosity = 1;
      break;
    case '?':
      printf("Given Option: %c\n", option);
    default:
      errno = 0;
      helpme();
    } /* switch x */
  }   /* while getopt */
argsFinished:;

  signal(SIGINT, &getctrlc);

  // if (globalArgs.bFreeConsole)
  // {
  //     FreeConsole();
  // }

  switch (globalArgs.method)
  {
  case LISTEN:
    bind2bind(globalArgs);
    break;
  case TRAN:
    bind2conn(globalArgs);
    break;
  case SLAVE:
    conn2conn(globalArgs);
    break;

  case SSOCKSD:
    ssocksd(globalArgs);
    break;
  case RCSOCKS:
    rcsocks(globalArgs);
    break;
  case RSSOCKS:
    rssocks(globalArgs);
    break;
  case NETCAT:
    netcat(argc, argv);
    break;
  default:
    helpme();
    break;
  }

  if (globalArgs.method) // cleanup
  {
    closeallfd();
  }

  return 0;
}