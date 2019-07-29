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
#include<sys/utsname.h>

void remin(char ** remcommand)
{
  int nm;
  int pid=fork();
  if(pid<0)
  perror("ERROR\n");
  if(pid==0)
  {
    sleep(atoi(remcommand[1]));
    for(nm=2;nm<count;nm++)
    printf("%s ",remcommand[i]);
    printf("\n");
  }
}