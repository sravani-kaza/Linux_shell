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

void displayprompt()
{
	char promptname[1024]={'\0'};
	strcat(promptname,"<");
	strcat(promptname,getenv("USER"));
	strcat(promptname,"@");
	strcat(promptname,hostname);
	strcat(promptname,":");
	printf("%s%s>",promptname,path);
}