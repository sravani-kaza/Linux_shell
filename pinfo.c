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

void pinfo(char **c)
{
	FILE * fp;
	char buf1[10000];
	char buf2[10000];
	int fl,pid;
	char name[1000],state;
	char name2[1000];
	long unsigned int size;


	printf("pid ---");
	printf("%d\n",getpid() );

	printf("Process Status -- ");
	if(!c[1] || strcmp(c[1]," ")==0)
	{
		sprintf(buf1,"/proc/%d/stat",getpid());
		sprintf(buf2,"/proc/%d/exe",getpid());
		fl=0;
	}
	else
	{
		sprintf(buf1,"/proc/%d/stat",c[1]);
		sprintf(buf2,"/proc/%d/exe",c[1]);
		fl=1;
	}
	if((fp=fopen(buf1,"r"))!=NULL)
	{
		fscanf(fp,"%d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d",&pid,&state,&size);
		fclose(fp);
		printf("pid -- %d\nProcess Status -- %c\nmemory -- %lu\n",pid,state,size);
		if(fl==0)
		{
			readlink(buf2,name,1000);
			printf("Executable Path -- ~/a.out\n");
		}
		else
		{
			int number=readlink(buf2,name,1000);
			name[number]='\0';
			printf("Executable Path -- %s\n",name);
		}

	}
	else
		perror("Error");




}