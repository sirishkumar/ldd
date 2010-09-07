#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile int signaled = 0;

void handler (int signum) {
  printf("signaled called\n");
  signaled = 1;
}

int main() {
  char ch;
  struct sigaction sigact;
  sigact.sa_handler = handler;
  sigact.sa_flags = SA_RESTART;
  sigaction(SIGINT, &sigact, NULL);

  while (read(STDIN_FILENO, &ch, 1) != 1 && !signaled);
}
