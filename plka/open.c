#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<malloc.h>

int main() {
  int handle, bytes;
  void* ptr;

  handle = open("/tmp/test.txt", O_RDONLY);

  ptr = (void*)malloc(150);

  bytes = read(handle, ptr, 150);
  printf("%s", ptr);

  close(handle);
  return 0;
}

