#include<stdio.h>

int main() {
  unsigned int val = 49; 
  unsigned int res;

  unsigned int mask = 1;
  mask <<= 5; 
  mask -= 1; printf("mask: %u\n", mask);

  res = val & mask;
  printf("val, res: %u, %u\n", val, res);
}
