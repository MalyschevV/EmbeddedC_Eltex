#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 5
#define INCREMENT 500
#define SLEEP_TIME 2
#define NUM_OF_CUSTOMERS 3
#define CUSTOMER_REQUIRMENTS 10000
#define INITIAL_VALUE_OF_STORE 1000

typedef struct Store {
  int value;
  pthread_mutex_t lock;
} Store;

Store stores[SIZE];

int customer_value[NUM_OF_CUSTOMERS];

void red() { printf("\033[1;31m"); }

void green() { printf("\033[0;32m"); }

void blue() { printf("\033[0;36m"); }

void* Loader(void* arg) {
  srand(time(NULL));
  int shop_index;

  while (1) {
    int status = 0;
    for (int i = 0; i < NUM_OF_CUSTOMERS; i++) {
      if (customer_value[i] <= 0) {
        status++;
      }
    }
    if (status == NUM_OF_CUSTOMERS) {
      sleep(SLEEP_TIME);
      printf(
          "All customers has satisfied his needs\nLoader has finished its "
          "work\n");
      pthread_cancel(pthread_self());
      exit(0);
    }

    shop_index = rand() % SIZE;
    pthread_mutex_lock(&stores[shop_index].lock);
    green();
    printf("Loader is unloading to the store = %d\n", shop_index + 1);
    stores[shop_index].value += INCREMENT;
    printf("Current state of stores:\n");
    for (int i = 0; i < SIZE; i++) {
      printf("%d ", stores[i].value);
    }
    printf("\n");
    pthread_mutex_unlock(&stores[shop_index].lock);

    sleep(SLEEP_TIME);
  }
  return NULL;
}

void* Customer(void* arg) {
  srand(time(NULL));
  int thread_num = *(int*)arg;
  int shop_index;

  while (1) {
    if (customer_value[thread_num] <= 0) {
      blue();
      printf("%d Customer has satisfied his needs\n", thread_num + 1);
      pthread_cancel(pthread_self());
      sleep(SLEEP_TIME - 1);
    } else {
      shop_index = rand() % SIZE;
      pthread_mutex_lock(&stores[shop_index].lock);
      red();
      printf("%d Customer visited %d shop his needed = %d\n", thread_num + 1,
             shop_index + 1, customer_value[thread_num]);
      customer_value[thread_num] -= stores[shop_index].value;
      printf("Then %d customer needed = %d\n", thread_num + 1,
             customer_value[thread_num]);
      stores[shop_index].value = 0;
      printf("Current state of stores:\n");
      for (int i = 0; i < SIZE; i++) {
        printf("%d ", stores[i].value);
      }
      printf("\n");
      pthread_mutex_unlock(&stores[shop_index].lock);

      sleep(SLEEP_TIME - 1);
    }
  }
  return NULL;
}

int main() {
  pthread_t loader_thread;
  int thread_num_of_customer[NUM_OF_CUSTOMERS];
  pthread_t customer_thread[NUM_OF_CUSTOMERS];

  for (int i = 0; i < SIZE; i++) {
    stores[i].value = INITIAL_VALUE_OF_STORE;
    pthread_mutex_init(&stores[i].lock, NULL);
  }

  for (int i = 0; i < NUM_OF_CUSTOMERS; i++) {
    customer_value[i] = CUSTOMER_REQUIRMENTS;
  }

  printf("Initial state of stores:\n");
  for (int i = 0; i < SIZE; i++) {
    printf("%d ", stores[i].value);
  }
  printf("\n");

  if (pthread_create(&loader_thread, NULL, Loader, NULL) != 0) {
    printf("Failed to create thread\n");
    return 1;
  }

  for (int i = 0; i < NUM_OF_CUSTOMERS; i++) {
    thread_num_of_customer[i] = i;
    if (pthread_create(&customer_thread[i], NULL, Customer,
                       &thread_num_of_customer[i]) != 0) {
      printf("Failed to create thread\n");
      return 1;
    }
  }

  for (int i = 0; i < NUM_OF_CUSTOMERS; i++) {
    if (pthread_join(customer_thread[i], NULL) != 0) {
      printf("Failed to join thread\n");
      return 1;
    }
  }

  if (pthread_join(loader_thread, NULL) != 0) {
    printf("Failed to join thread\n");
    return 1;
  }
  return 0;
}