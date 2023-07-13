#include <pthread.h>
#include <stdio.h>
#define THREADS 1000
#define VALUE 1000000

long sum = 0;

void *ThreadRace(void *args) {
  for (int i = 0; i < VALUE; i++) {
    sum++;
  }
}

int main() {
  pthread_t thread_array[THREADS];
  long *ptr = NULL;
  long array[THREADS];

  for (int i = 0; i < THREADS; i++) {
    array[i] = i;
    pthread_create(&thread_array[i], NULL, ThreadRace, (void*)&array[i]);
  }

  for (int i = 0; i < THREADS; i++) {
    pthread_join(thread_array[i], (void **)&ptr);
  }

  printf("sum = %ld\n", sum);
  
  return 0;
}