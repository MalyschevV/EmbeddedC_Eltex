#include <stdio.h>

int main() {
  int number = 0xDDCCBBAA;
  int mask = 0x000000FF;
  unsigned char byte_of_number = 0;
  int new_value = 0x00EE0000;
  int new_number = 0x00000000;
  int changed_byte = 3;
  int shift = 0;
  for (int i = 0; i < sizeof(int); i++) {
    byte_of_number = ((number >> shift) & mask);
    printf("%d byte of a = %x\n", i + 1, byte_of_number);
    if (i != changed_byte - 1) {
      new_number = new_number + (number & (mask << shift));
    } else {
      new_number = new_number + (new_value & (mask << shift));
    }
    shift = shift + 8;
  }
  printf("\nchanged 3 byte of a number, new value: %x\n", new_number);
  return 0;
}
