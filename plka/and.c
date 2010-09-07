#include <stdio.h>

int main() {
  int val1 = 4;
  int val2 = 8;
  
  if (val1 & val2) {
    printf("And\n");
  }

  if (val1 && val2) {
    printf("And and\n");
  }
}
