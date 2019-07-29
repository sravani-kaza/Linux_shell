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

void bg_execute(char ** execcommand)
{
	int cn;
	cn=atoi(execcommand[1]);
	if(cn>num_backp)
	{
		printf("PROCESS DOESNOT EXIST\n");
	}
	else
	{
		if(kill(back_process_arr[cn-1].pid_val,SIGCONT)==-1)
			perror("ERROR");
		else
			back_process_arr[cn-1].pid_status=0;
	}
}