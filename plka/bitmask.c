int main() {
  int val1 = 33; 
  int val2 = 18;

  int mask = 1;
  mask <<= 4; 

  if (val1 & mask) {
    printf("Bit 5 in val1 is set\n");
  }

  if (val2 & mask) {
    printf("Bit 5 in val2 is set\n");
  }
}
