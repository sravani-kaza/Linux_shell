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

char ** divide(char * givencom,char * del)
{
	//printf("%s\n",givencom );
	char** j=malloc(sizeof(char*)*1000);
	token=strtok(givencom,del);
	int num=0;
	char ** retcommand;
	while(token != NULL)
	{
		j[num]=token;
		num++;
		token=strtok(NULL,del);
	}
	if(del[0]==' ')
		count=num;
	if(del[0]==';')
		n=num;
	if(del[0]=='|')
		count_p=num;
	//printf("%d %s\n",num,del);
	return j;

}