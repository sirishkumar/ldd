/* Simple replacement for strace(1) */

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/ptrace.h>
#include<sys/wait.h>
#include<asm/ptrace.h>    /* for ORIG_EAX */

static long pid;

int upeek(int pid, long off, long *res) {
  long val;

  val = ptrace(PTRACE_PEEKUSER, pid, off, 0);

  if (val == -1) {
    return -1;
  }

  *res = val;
  return 0;
}

void trace_syscall() {
  long res;

  res = ptrace(PTRACE_SYSCALL, pid, (char*) 1, 0);
  if (res < 0) {
    printf("Failed to execute until next syscall: %d\n", res);
  }
}

void sigchld_handler (int signum) {
  long scno;
  int res;

  /* Find out the system call (system-dependent)...*/
  if (upeek(pid, 4*ORIG_EAX, &scno) < 0) {
    return;
  }
  
  /* ... and output the information */
  if (scno != 0) {
    printf("System call: %u\n", scno);
  }

  /* Activate tracing until the next system call */
  trace_syscall();
}

int main(int argc, char** argv) {
  int res;
  
  /* Check the number of arguments */
  if (argc != 2) {
    printf("Usage: ptrace <pid>\n");
    exit(-1);
  }

  /* Read the desired pid from the command-line parameters */
  pid = strtol(argv[1], NULL, 10);
  if (pid <= 0) {
    printf("No valid pid specified\n");
    exit(-1);
  } else {
    printf("Tracing requested for PID %u\n", pid);
  }
  
  /* Install handler for SIGCHLD */
  struct sigaction sigact;
  sigact.sa_handler = sigchld_handler;
  sigaction(SIGCHLD, &sigact, NULL);  

  /* Attach to the desired process */
  res = ptrace(PTRACE_ATTACH, pid, 0, 0);
  if (res < 0) {
    printf("Failed to attach: %d\n", res);
    exit(-1);
  } else {
    printf("Attached to %u\n", pid);
  }
  
  for (;;) {
    wait(&res);
    if (res == 0) {
      exit(1);
    }
  }
}
