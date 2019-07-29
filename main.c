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
#include <signal.h>



int main()
{
	shellpid=getpid();
	//printf("%d\n",shellpid );
	char acthome[1024];
	prevpath="~";
	cur_dir="~";
	path[0]= '~';
	getcwd(acthome,sizeof(acthome));			//where the file runs
	gethostname(hostname,1024);
	int cdcom=0;
	displayprompt();
	signal(SIGINT, sigintHandler);
	signal(SIGTSTP, sigtstpHandler);
	while(1)
	{	
		//displayprompt();
		//printf("hgf");
		pid_fore=-1;
		int hd=strlen(fore_name);
		for(int u=0;u<hd;u++)
			fore_name[u]='\0';
		cdcom=0;
		char * command=malloc(sizeof(char) * 1024);
		size_t csize=1024;
		getline(&command,&csize,stdin);
		int leng;
		leng=strlen(command);
		command[leng-1]='\0';

		//printf("yaa\n");

		subcommand=divide(command,";");


		//printf("n=%d\n",n );
		int noc=n;
		for(j=0;j<noc;j++)
		{
			//printf("hello\n");
			int pipecheck=checkpipe(subcommand[j]);
			//printf("wow\n");
			if(pipecheck)
			{
				//printf("YES\n");
				pipe_execute(subcommand[j]);
				displayprompt();
				continue;
			}
			eachcommand=divide(subcommand[j]," ");
			if(strcmp(eachcommand[0],"quit")==0)
			{	
				int d;
			    for(d=0; d<num_backp; d++)
				{  
			    	kill(back_process_arr[d].pid_val, 9);
			    		//perror("ERROR");
			    }
				return 0;
			}
			else if(strcmp(eachcommand[0],"exit")==0)
			{
				int d;
			    for(d=0; d<num_backp; d++)
			    {  
			    	kill(back_process_arr[d].pid_val, 9);
			    }
				return 0;
			}
			else if(strcmp(eachcommand[0],"echo")==0)
			{
				for(i=1;i<count;i++)
				{
					if(eachcommand[i][0]!='$')
						printf("%s ",eachcommand[i] );
					else
					{	
						printf("hrer\n");
						int z1=strlen(eachcommand[i]);
						char s[1024]={'\0'};
						printf("z=%d\n",z1);
						int q;
						for(q=1;q<z1;q++)
						{	s[q-1]=eachcommand[i][q];
							//printf("%d\n",q );
						}
						s[q-1]='\0';
						//printf("hii\n");
						//printf("%s\n",s );
						printf("%s\n",getenv(s));
					}

				}
				printf("\n");
			}
			else if(strcmp(eachcommand[0],"pwd")==0)
			{				
				printf("%s\n",path );				
			}
			else if(strcmp(eachcommand[0],"cd")==0)
			{
				cdcom=1;
				if(count==1)
					eachcommand[1]="~";
				//printf("hello\n");
				cd(acthome,eachcommand[1]);
			}
			else if(strcmp(eachcommand[0],"pinfo")==0)
			{
				pinfo(eachcommand);
			}
			else if(strcmp(eachcommand[0],"ls")==0)
			{
				//printf("yes\n");
				if(count==1)
					eachcommand[count]=".";
				ls(eachcommand);
				//printf("hiii\n");
			}
			else if(strcmp(eachcommand[0],"remaindme")==0)
			{
				remin(eachcommand);
			}
			else if(strcmp(eachcommand[0],"setenv")==0)
			{
				setenv_execute(eachcommand);
			}
			else if(strcmp(eachcommand[0],"unsetenv")==0)
			{
				unsetenv_execute(eachcommand);
			}
			else if(strcmp(eachcommand[0],"jobs")==0)
			{
				jobs_execute(eachcommand);
			}
			else if(strcmp(eachcommand[0],"kjob")==0)
			{
				if(count==3)
				{
					kjob_execute(eachcommand);
				}
				else
					printf("CHECK ARGUMENTS\n");
			}
			else if (strcmp(eachcommand[0], "bg") == 0)
			{
			 	if(count!=2)
			 	{
			 		printf("CHECK ARGUMENTS\n");
			 	}   
			 	else
			 	{
			 		bg_execute(eachcommand);
			 	}
			}
			else if (strcmp(eachcommand[0], "fg") == 0)
			{
			    if(count!=2)
			    {
			    	printf("CHECK ARGUMENTS\n");
			    }
			    else
			    {
			    	fg_execute(eachcommand);
			    }
			}
			else if(strcmp(eachcommand[0], "overkill") == 0)
			{
				int d;
			    for(d=0; d<num_backp; d++)
			    {  
			    	if(kill(back_process_arr[d].pid_val, 9)==-1)
			    		perror("ERROR");
			    }
			}
			else
			{
				//printf("I am");
				cdcom=1;
				fore_background(eachcommand);
			}
			if(cdcom==0)
				displayprompt();

		}
		//break;
	}

	return 0;
}
