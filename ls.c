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

int r;
static char perms_buff[30];
const char *get_perms(mode_t mode)
{
	char ftype='?' ;

	if (S_ISREG(mode)) ftype = '-';
	if (S_ISLNK(mode)) ftype = 'l';
	if (S_ISDIR(mode)) ftype = 'd';
	if (S_ISBLK(mode)) ftype = 'b';
	if (S_ISCHR(mode)) ftype = 'c';
	if (S_ISFIFO(mode)) ftype = '|';

	sprintf(perms_buff, "%c%c%c%c%c%c%c%c%c%c %c%c%c", ftype,
			mode & S_IRUSR ? 'r' : '-',
			mode & S_IWUSR ? 'w' : '-',
			mode & S_IXUSR ? 'x' : '-',
			mode & S_IRGRP ? 'r' : '-',
			mode & S_IWGRP ? 'w' : '-',
			mode & S_IXGRP ? 'x' : '-',
			mode & S_IROTH ? 'r' : '-',
			mode & S_IWOTH ? 'w' : '-',
			mode & S_IXOTH ? 'x' : '-',
			mode & S_ISUID ? 'U' : '-',
			mode & S_ISGID ? 'G' : '-',
			mode & S_ISVTX ? 'S' : '-');

	return (const char *)perms_buff;
}

char pathname[MAXPATHLEN];
char pathname1[MAXPATHLEN];

void die(char *msg)
{
	perror(msg);
	exit(0);
}

	static int
one (const struct dirent *unused)
{
	return 1;
}


void ls(char **execcommand)
{
	if(!getcwd(pathname, sizeof(pathname)))
		die("Error getting pathname");
	int gh;
	int afound=0;
	int lfound=0;
	//printf("c=%d\n",count);
	//printf("%s\n",execcommand[1] );
	for(gh=1;gh<count;gh++)
	{
		if(strcmp("-l",execcommand[gh])==0)
			lfound=1;
		if(strcmp("-a",execcommand[gh])==0)
			afound=1;
		if(strcmp("-al",execcommand[gh])==0 || strcmp("-la",execcommand[gh])==0)
		{
			lfound=1;
			afound=1;
		}
		//printf("l=%d,c=%d\n",lfound,afound );
	}
	//printf("l=%d,c=%d\n",lfound,afound );
	int count1,i1,l1;
	struct direct **files;
	struct stat statbuf;
	char datestring[256];
	struct passwd pwent;
	struct passwd *pwentp;
	struct group grp;
	struct group *grpt;
	struct tm time;
	char buf[1024];
	char *jd;
	if(strcmp("-la",execcommand[1])!=0 && strcmp("-al",execcommand[1])!=0 && strcmp("-a",execcommand[1])!=0 && strcmp("-l",execcommand[1])!=0)
	{
		//strcpy(pathname1,pathname);
		int length=strlen(pathname);
		if(execcommand[1][0]=='.' && execcommand[1][1]=='/')
		{
			int lm=1;
			while(execcommand[1][lm]!='\0')
			{
				pathname[length+lm-1]=execcommand[1][lm];
				lm++;
			}
			//pathname[length+lm-1]="/0";
		}
		else	
		{	if(execcommand[1][0]!='/')
				strcat(pathname,"/");
			else
			{
				printf("ERROR:No such file exists\n");
				//return;
			}
			strcat(pathname,execcommand[1]);
		}
		printf("%s\n",pathname );	
	}
	count1 = scandir(pathname, &files, one, alphasort);
	if(count1<0)
		perror("ERROR");
		if(count1 > 0)
		{
			l1=0;
			//printf("reached");
			if(lfound==1 && afound==0)
			{

				
				//printf(":lkj");
				for (i1=0; i1<count1; ++i1)
				{
					if (stat(files[i1]->d_name, &statbuf) == 0)
					{

						if(files[i1]->d_name[0]!='.')
						{
							printf("%10.10s", get_perms(statbuf.st_mode));
							printf(" %d", statbuf.st_nlink);

							if (!getpwuid_r(statbuf.st_uid, &pwent, buf, sizeof(buf), &pwentp))
								printf(" %s", pwent.pw_name);
							else
								printf(" %d", statbuf.st_uid);

							if (!getgrgid_r (statbuf.st_gid, &grp, buf, sizeof(buf), &grpt))
								printf(" %s", grp.gr_name);
							else
								printf(" %d", statbuf.st_gid);

							// Print size of file. 
							printf(" %5d", (int)statbuf.st_size);

							localtime_r(&statbuf.st_mtime, &time);
							// Get localized date string. 
							strftime(datestring, sizeof(datestring), "%F %T", &time);
							//printf("1 %s",files[i]->d_name);
							printf(" %s %s\n", datestring, files[i1]->d_name);
						}
						else
							l1++;
					}

					free (files[i1]);
				}


				free(files);
				printf("total %d\n",count1-l1);
			}
			if(afound==1 && lfound==1)
			{
				//printf("total %d\n",count1);

				for (i1=0; i1<count1; ++i1)
				{
					if (stat(files[i1]->d_name, &statbuf) == 0)
					{


						printf("%10.10s", get_perms(statbuf.st_mode));
						printf(" %d", statbuf.st_nlink);

						if (!getpwuid_r(statbuf.st_uid, &pwent, buf, sizeof(buf), &pwentp))
							printf(" %s", pwent.pw_name);
						else
							printf(" %d", statbuf.st_uid);

						if (!getgrgid_r (statbuf.st_gid, &grp, buf, sizeof(buf), &grpt))
							printf(" %s", grp.gr_name);
						else
							printf(" %d", statbuf.st_gid);

						// Print size of file. 
						printf(" %5d", (int)statbuf.st_size);

						localtime_r(&statbuf.st_mtime, &time);
						// Get localized date string. 
						strftime(datestring, sizeof(datestring), "%F %T", &time);
						//printf("1 %s",files[i]->d_name);
						printf(" %s %s\n", datestring, files[i1]->d_name);

					}

					free (files[i1]);
				}

				printf("total %d\n",count1);
				free(files);


			}
			if(afound==1 && lfound==0)
			{
				for (i1=0; i1<count1; ++i1)
				{
					if (stat(files[i1]->d_name, &statbuf) == 0 )
					{
						printf("%s\n", files[i1]->d_name);
					}
					free (files[i1]);
				}
				printf("total %d\n",count1);

				free(files);

			}

			if(afound==0 && lfound==0)
			{
				printf("hello\n");
				for (i1=0; i1<count1; ++i1)
				{
					if (stat(files[i1]->d_name, &statbuf) == 0 && files[i1]->d_name[0]!='.')
					{
						printf("%s\n", files[i1]->d_name);
					}
					else
						l1++;
					free (files[i1]);
				}

				printf("total %d\n",count1-l1);
				free(files);

			}
		}

}