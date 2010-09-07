#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

#define SEMKEY 1234L      /* Identifier */
#define PERMS  0666       /* Access permission: rwrwrw */

struct sembuf op_down[1] = { 0, -1 , 0 };
struct sembuf op_up[1] = { 0, 1 , 0 };

int semid = -1;   /* Semaphore identifier */
int res;          /* Result of semaphore operations */

void init_sem() {
  /* Test whether semaphore already exists */
  semid = semget(SEMKEY, 0, IPC_CREAT | PERMS);
  if (semid < 0) {
    printf("Create the semaphore\n");
    
    semid = semget(SEMKEY, 1, IPC_CREAT | PERMS);
    if (semid < 0) {
      printf("Couldn't create semaphore!\n");
      exit(-1);
    }
    
    /* Initialize with 1 */
    res = semctl(semid, 0, SETVAL, 1);
  }
}

void down() {
  /* Perform down operation */
  res = semop(semid, &op_down[0], 1);
}

void up() {
  /* Perform up operation */
  res = semop(semid, &op_up[0], 1);
}


int main(){
  init_sem();
  /* Normal program code. */

  printf("Before critical code\n");
  down();
  /* Critical code */
  printf("In critical code\n");
  sleep(10);
  up();

  /* Remaing program code */
  return 0;
}
