#include<sys/types.h>
#include<stdio.h>

pid_t shellpid;
pid_t pid_fore;
char fore_name[1024];
char hostname[1024];                                    
char ** subcommand;                                
char * cur_dir;
char * prevdir;
char path[1024] ;
char * prevpath;
int i,j,k,l,a,fd1;
char * token;
int n,count;
char ** eachcommand;
char ** eachpipecommand;
int count_p;
char * setv[1024];
char  * varval[1024];
typedef struct back_process
{	char name_of_process[1024];
	pid_t pid_val;
	pid_t pid_status;
}stback;						//process info
stback back_process_arr[1024];	//stores background-process
int num_backp;


void displayprompt();
char ** divide(char *givencom,char * del);
void fore_background(char ** executecommand);
void funct();
void remin(char ** remcommand);
void pinfo(char **c);
void ls(char **execcommand);
void cd(char * home,char * dir);
void pipe_execute(char * execcommand);
int checkpipe(char * execcommand);
char **redirect_execute(char **execcommand);
void setenv_execute(char *setv[]);
void unsetenv_execute(char *setv[]);
void jobs_execute(char ** execcommand);
void fg_execute(char ** execcommand);
void bg_execute(char ** execcommand);
void sigintHandler(int sig_num);
void sigtstpHandler(int sig_num);
void sigHandler1(int sig_num);