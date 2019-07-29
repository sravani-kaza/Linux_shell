#include "headerfile.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pwd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<errno.h>
#include<string.h>
#include <netdb.h>
#include <sys/param.h>
#include <sys/wait.h>
#include <sys/dir.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>
#include <fcntl.h>
#include<signal.h>

void setenv_execute(char *setv[])
{
	if(setenv(setv[1],setv[2],1)==-1)
		perror("ERROR");
	//printf("%s",getenv(setv[1]));
}

void unsetenv_execute(char *setv[])
{
	if(unsetenv(setv[1])==-1)
		perror("ERROR");
	//printf("%s",getenv(setv[1]));
}
