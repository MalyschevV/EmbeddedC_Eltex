#include "plugin.h"

void PluginLoader(const char *path, const char *name) {
  int first_number, second_number, result = 0;
  int (*function)(int first_number, int second_number);
  
  void *handler = dlopen(path, RTLD_NOW);
  if (handler == NULL) {
    fprintf(stderr, "dlopen() error: %s\n", dlerror());
    return;
  }

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