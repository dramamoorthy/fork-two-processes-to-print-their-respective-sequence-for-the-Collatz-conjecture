

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void recursivePrintCollatz(int arg, int n)
{
  if(arg == 1)
     printf("From Child %d n = %d \n", n, arg);
  else{
  if(arg%2==0){
     printf("From Child %d n = %d \n", n, arg);
     recursivePrintCollatz(arg/2, n);
               }
   else{
       printf("From Child %d n = %d \n", n, arg);
       recursivePrintCollatz(3*arg +1, n);
       }
      }
      
}

int main(int argc, const char * argv[])
{

    int status1, status2, pid1, pid2, a;
    a = atoi(argv[1]);

    if(argc==2&&(a>0&&a<40)){
      if((pid1=fork())<0){
        printf("forking failed \n");
        exit(1);
      }

      else if(pid1 == 0){
        recursivePrintCollatz(a,1);
      }
      waitpid(pid1, &status1, WUNTRACED);
      if(WIFEXITED(status1))
        printf("Child 1 Done !\n");
      if((pid2=fork())<0){
        printf("forking failed \n");
        exit(1);
      }
      else if(pid2 == 0){
        recursivePrintCollatz(a+4, 2);
        }
        waitpid(pid2, &status2,WUNTRACED);
      if(WIFEXITED(status2)){
                printf("Children Complete\n");
                kill(pid1, SIGKILL);
                kill(pid2, SIGKILL);
      }
      return 0;
   }
   else{
        printf("Enter a positive number less than 40");
   }
}
