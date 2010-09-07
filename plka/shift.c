#include<stdio.h>

int main() {
  unsigned int val = 1;
  unsigned int count;

  for (count = 0; count <= 10; count++) {
    printf("count, val: %u, %u\n", count, val);
    val <<= 1;
  }
}

