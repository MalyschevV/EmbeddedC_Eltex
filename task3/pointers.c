#include <stdio.h>

int main() {
  int number = 270533154;
  char *ptr = NULL;
  ptr = &number;
  int changed_number = 3;
  unsigned char value_of_changed_number = 54;
  printf("\nbyte value of a number:\n");
  for (int i = 0; i < sizeof(int); i++) {
    printf("%d byte of number = %d\n", i + 1, *ptr);
    ptr++;
  }
  ptr = NULL;
  ptr = &number;
  for (int i = 0; i < sizeof(int); i++) {
    if (i == changed_number - 1) {
      *ptr = value_of_changed_number;
      printf("\nnew 3 byte of number = %d\n", *ptr);
    }
    ptr++;
  }
  ptr = NULL;
  ptr = &number;
  printf("\nnew byte value of a number:\n");
  for (int i = 0; i < sizeof(int); i++) {
    printf("%d byte of number = %d\n", i + 1, *ptr);
    ptr++;
  }
  return 0;
}
