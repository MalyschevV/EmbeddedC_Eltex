#include <dlfcn.h>
#include <stdio.h>
#define SIZE 127

void PluginLoader(const char *path, const char *name) {
  void *handler = dlopen(path, RTLD_NOW);
  int first_number, second_number, result = 0;
  if (handler == NULL) {
    fprintf(stderr, "dlopen() error: %s\n", dlerror());
    return;
  }
  int (*function)(int first_number, int second_number);
  function = dlsym(handler, name);
  if (function == NULL) {
    fprintf(stderr, "dlsym() error: %s\n", dlerror());
  } else {
    printf("\n");
    printf("First number >> ");
    scanf("%d", &first_number);
    printf("Second number >> ");
    scanf("%d", &second_number);
    result = function(first_number, second_number);
    printf("Result = %d\n", result);
  }
  dlclose(handler);
}

int main() {
  int quantity = 0;
  int choice = 0;
  printf(
      "Welcome to dynamic calculator!\nPlease enter the quantity of "
      "arithmetic operations\n");
  scanf("%d", &quantity);
  if (quantity > 4) {
    printf("Error: too many arifmetic operators!");
    return -1;
  } else if (quantity < 1) {
    printf("Error: too few arifmetic operators!");
    return -1;
  }
  char path[quantity][SIZE];
  char func_name[quantity][SIZE];
  printf(
      "Select operations to form menu in the format --> ./{name of library}.so "
      "{name of function}.\nExample for addition: ./libaddition.so addition\n");
  for (int i = 0; i < quantity; i++) {
    scanf("%s%s", path[i], func_name[i]);
  }
  while (1) {
    for (int i = 0; i <= quantity; i++) {
      if (i == quantity) {
        printf("\nEnter %d to exit.\n", i + 1);
        break;
      }
      printf("\nEnter %d to %s\n", i + 1, func_name[i]);
    }
    scanf("%d", &choice);
    if (choice == quantity + 1) {
      return 0;
    }
    PluginLoader(path[choice - 1], func_name[choice - 1]);
  }
  return 0;
}
