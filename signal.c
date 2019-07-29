#include "headerfile.h"
#include <stdio.h> 
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void sigintHandler(int sig_num) 
{ 
   
  
    //signal(SIGINT, sigintHandler); 

	if(sig_num==SIGINT)
	{
		if(pid_fore!=-1)
		{	

			//printf("hello\n");
			if(kill(pid_fore,SIGINT)<0)
				perror("ERROR");
			//sigintHandler(sig_num);
    		fflush(stdout); 
    		//displayprompt();
    	}
    }

} 

void sigtstpHandler(int sig_num) 
{ 
    

	if(sig_num==SIGTSTP)
	{
		//pid_t pre_pid=getpid();
		//printf("hii\n");
		//printf("gp%d\n",getpid() );
		//printf("fg%d\n",pid_fore );
		//printf("sp%d\n",shellpid );
		if(pid_fore!=-1)
		{
			//printf("hello\n");	
			if(kill(pid_fore,SIGSTOP)<0)
				perror("ERROR");
			else
			{
				strcpy(back_process_arr[num_backp].name_of_process, fore_name);
				//printf("hiii1\n");
				back_process_arr[num_backp].pid_val = pid_fore;
				back_process_arr[num_backp].pid_status = 1;
				num_backp++;
			}
			//displayprompt();
			//printf("hy\n");
    	}
    }

} 

void sigHandler1(int sig_num)
{
	//do nothing	
	if(sig_num==SIGTSTP)
	{
		return;
	}
}