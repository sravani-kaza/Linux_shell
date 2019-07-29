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
#include<signal.h>

int checkpipe(char * execcommand)
{
	int e;
	for(e=0;e<strlen(execcommand);e++)
	{
		if(execcommand[e]=='|')
			return 1;
	}
	return 0;
}
void pipe_execute(char * execcommand)
{
	int fildes1[2];
	int fildes2[2];
	if(pipe(fildes1) != 0)
	{  	
		perror("pipe1 failed");
		return;
	}
	if(pipe(fildes2)!=0)
	{
		perror("pipe2 failed");
		return;
	}
	char ** pipecommand=divide(execcommand,"|");
	if(count_p==1)
	{
		printf("ERROR\n");
		return;
	}
	//printf("%d\n",count_p );
	int h;
	char ** pipeeachcommand;
	for(h=0;h<count_p;h++)
	{
		pipeeachcommand=divide(pipecommand[h]," ");
		//printf("h=%d\n",h );
		
		//printf("no=%d\n",count_p );
		int pid=fork();
		{	//printf("inside id h=%d\n",h );
			if(pid<0)
				perror("ERROR");
			else if(pid==0)
			{
				//printf("inside pid=0h=%d\n",h );
				//printf("hii");
				if(h%2==1)
				{
					if(h+1!=count_p)
					{
						if(dup2(fildes2[1],1)==-1)
							perror("dup2 failed1");
					}
					if(h!=0)
					{
						if(dup2(fildes1[0],0)==-1)
							perror("dup2 failed2");
					}
				}
				else
				{
					if(h+1!=count_p)
					{
							if(dup2(fildes1[1],1)==-1)
								perror("dup2 failed3");
					}
					if(h!=0)
					{
						if(dup2(fildes2[0],0)==-1)
							perror("dup2 failed4");
					}
				}
				//printf("afetr h=%d\n",h );
				char ** fgh;
				//int k=0;
				//for(k=0;k<count;k++)
				//	printf("%s\n",pipeeachcommand[k] );
				//printf("count=%d\n",count );
				//printf("h=%d\n",h );
				fgh=redirect_execute(pipeeachcommand);
				//printf("h=%d\n",h );
				//for(k=0;k<count;k++)
				//	printf("%s\n",fgh[k] );
				execvp(fgh[0],fgh);
			}
			else
			{
				//printf("y\n");
				if(h%2==1)
				{
					if(h+1!=count_p)
						close(fildes1[0]);
					if(h!=0)
						close(fildes2[1]);
				}
				else
				{
					if(h+1!=count_p)
						close(fildes1[1]);
					if(h!=0)
						close(fildes2[0]);
				}
				wait(NULL);
			}
		}
	}
}