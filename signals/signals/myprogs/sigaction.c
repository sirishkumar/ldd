#include <stdio.h>
#include <signal.h>

void handler(int signum)
{
   printf("\nIn handler with signum %d",signum);
}

int main()
{

  struct sigaction sa;
  int counter;
  sigset_t set;

  sigemptyset(&set);

  sa.sa_handler = handler;

  //! DO not blcok any signals during execution of handler
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;

  sigaction(SIGTERM,&sa,NULL);
  sigaction(SIGSTOP,&sa,NULL);
  
  //! Block sa_mask i.e, in this case block no signals
  sigprocmask(SIG_BLOCK|SIG_SETMASK,&set,NULL);

  while(1){
     //! apply mask sa_mask and wait untill other signal is triggered
     sigsuspend(&sa.sa_mask);
     printf("\nloop");
  }
    
return 0;
}
