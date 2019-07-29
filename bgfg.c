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


void funct()
{
  //printf("hiii4\n");
  int backg,status;
  backg=waitpid(-1,&status,WNOHANG);

  	
    if(WIFEXITED(status)==1 && backg>0)
    {
      printf("\nprocess with pid %d exited normally\n",backg);
    }
    else if(WIFSIGNALED(status)==1 && backg>0)
    {
      printf("\nProcess with pid %d was interrupted by signal %d\n",backg,WTERMSIG(status));
    }
    else
    {
    	//do nothing
    }
    //printf("hiii5\n");
  return;
}

void fore_background(char ** executecommand)
{
	int background =0;
	int g;
	int back_pid;
	//printf("%s\n",executecommand[count-1] );
	if(strcmp(executecommand[count-1],"&")==0 )
	{	
		background=1;
		executecommand[count-1]=NULL;
	}
	int pid=fork();
	if(pid<0)
		perror("Error\n");
	else if(pid==0)
	{
		if(background)
		{	
			//signal(SIGINT,SIG_IGN);
			//if(setpgid(0,0)!=0)
			//	perror("ERROR");
			//signal(SIGINT,sigHandler1);
			
		}
		executecommand=redirect_execute(executecommand);
		
		g=execvp(executecommand[0],executecommand);
		if(g<0)
			perror("ERROR\n");
		exit(0);
	}					
	else
	{

		if(!background)
		{	
			
			pid_fore=pid;
			strcpy(fore_name,executecommand[0]);
			waitpid(pid, NULL,0);
			
		}
		else
		{
			strcpy(back_process_arr[num_backp].name_of_process, executecommand[0]);
			//printf("hiii1\n");
			back_process_arr[num_backp].pid_val = pid;
			//printf("hiii2\n");
			num_backp++;
		}
	}
	//printf("hiii3\n");
	displayprompt();

	signal(SIGCHLD,funct);

}
