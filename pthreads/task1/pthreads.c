#include <pthread.h>
#include <stdio.h>
#define THREADS 5

void *ThreadCalc(void *args) {
  int *ptr = (int *)args;
  printf("%d\n", *ptr);
  return NULL;
}

int main() {
  int thread_array[THREADS];
  int *ptr = NULL;
  pthread_t thread[THREADS];

  for (int i = 0; i < THREADS; i++) {
    thread_array[i] = i;
    pthread_create(&thread[i], NULL, ThreadCalc, (void *)&thread_array[i]);
  }

  for (int i = 0; i < THREADS; i++) {
    pthread_join(thread[i], (void **)&ptr);
  }

  return 0;
}