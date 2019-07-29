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

void kjob_execute(char **execcommand)
{
	int d=atoi(execcommand[1]);				
	int e=atoi(execcommand[1]);	
	if(d>num_backp)								//process doesnot exist
	{
		printf("PROCESS DOESNOT EXIST\n");
	}
	else
	{
		if(kill(back_process_arr[d-1].pid_val,e)!=0)  //kill process
			perror("ERROR");
	}
}