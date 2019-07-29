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

void jobs_execute(char ** execcommand)
{
  int q,procnum;
  pid_t curr;
  for(q=0;q<num_backp;q++)
  {
    curr = waitpid(back_process_arr[q].pid_val , &procnum,  WUNTRACED | WNOHANG );
    if(curr>0)
    {
      if(WIFCONTINUED(procnum) != 0)
        back_process_arr[q].pid_status = 0;

      else if(WIFSTOPPED(procnum) != 0)
        back_process_arr[q].pid_status = 1;
      
      else
      {
        //do nothing
      }
    }
    else if(curr<0)
    {
      //not completed remove process
      //intf("%s\n",back_process_arr[q].name_of_process );
      int ds;
      for(ds=q+1; ds <num_backp ; ds++)
              back_process_arr[ds-1] = back_process_arr[q];
      num_backp--;
    }
    else
    {  //perror("ERROR1");

    }
  }
  int yo;
  for(yo = 0; yo<num_backp; yo++)
    {
      char *proc_state;
      if(back_process_arr[yo].pid_status == 0)
         proc_state = "Running";
      else 
         proc_state = "Stopped";

        printf("[%d]  %s  %s [%d]\n", (yo+1), proc_state, back_process_arr[yo].name_of_process, back_process_arr[yo].pid_val);
    }
}