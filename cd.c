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

void cd(char * home,char * dir)
{
	char newpath[1024]={'\0'};
	if(chdir(dir)!=0)
		perror("ERROR");
	getcwd(newpath,sizeof(newpath));
	//printf("%s\n",newpath );
	int ln=strlen(home);
	int y=1;
	int g=strlen(path);
	for(int f=0;f<g;f++)
		path[f]='\0';
	path[0]='~';
	if(strlen(newpath)>strlen(home))
	{
		while(newpath[ln])
		{
			path[y]=newpath[ln];
			y++;
			ln++;
		}
	}
	else
	{
		y=strlen(path);
		int p;
		for(p=0;p<y;p++)
			path[p]='\0';
		path[0]='~';
	}
	displayprompt();

}