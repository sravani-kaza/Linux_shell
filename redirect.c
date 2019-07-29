#include "headerfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
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
#include <signal.h>
#include <sys/utsname.h>


char ** redirect_execute(char **execcommand)
{
	int d;
	int fd1,fd2,fd3;
	//printf("%d=countin re\n",count );
	for(d=0;d<count-1;d++)
	{
		//printf("%s\n",execcommand[d] );
		if(execcommand[d][0]=='<' && strlen(execcommand[d])==1 )
		{
			//printf("here\n");
			execcommand[d]=NULL;
			fd1=open(execcommand[d+1],O_RDONLY,0644);
			if(fd1<0)
			{	
				perror("ERROR");
			}
			dup2(fd1,0);
			close(fd1);

		}
		else if(execcommand[d][0]=='>' && strlen(execcommand[d])==1)
		{
			//printf("here1\n");
			execcommand[d]=NULL;
			//printf("Hgfj\n");
			fd2=open(execcommand[d+1],O_WRONLY|O_CREAT |O_TRUNC,0644);
			//printf("%s\n",execcommand[d+1] );
			if(fd2<0)
			{	
				perror("ERROR");
			}
			//printf("%d",fd1);
			dup2(fd2,1);
			//printf("jhk\n");
			close(fd2);
		}
		else if( execcommand[d][0]=='>' && execcommand[d][1]=='>' && strlen(execcommand[d])==2)	
		{
			//printf("here2\n");
			execcommand[d]=NULL;
			fd3=open(execcommand[d+1],O_WRONLY|O_CREAT |O_APPEND,0644);
			if(fd3<0)
			{	
				perror("ERROR");
			}
			dup2(fd3,1);
			close(fd3);
		}
		//printf("%s\n",execcommand[d] );
		else
		{
			//do nothing
		}
	}
	return execcommand;
}