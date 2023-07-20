#include "phonebook.h"

List *head = NULL;

List *CreateNewRecord(Phonebook *phonebook) {
  List *list = malloc(sizeof(list));
  list->data = phonebook;
  list->next = NULL;
  list->prev = NULL;
  return list;
}

void InsertRecord(List *list) {
  if (head == NULL) {
    head = list;
  } else {
    List *tmp = head;
    while (tmp->next != NULL) {
      tmp = tmp->next;
    }
    tmp->next = list;
    tmp->next->prev = tmp;
  }
  printf("\nRecord successfully added!\n\n");
}

void SearchRecordByNumber(long key) {
  List *tmp = head;

  if (head->data->number == key) {
    printf("\nFound record!\n\n");
    printf("number:%ld\n", head->data->number);
    printf("name:%s\n", head->data->name);
    printf("surname:%s\n", head->data->surname);
    return;
  }

  while (tmp->next != NULL) {
    tmp = tmp->next;
    if (tmp->data->number == key) {
      printf("\nFound record!\n\n");
      printf("number:%ld\n", tmp->data->number);
      printf("name:%s\n", tmp->data->name);
      printf("surname:%s\n", tmp->data->surname);
      return;
    }
  }

  printf("\nWrong Record!\n");
  return;
}

void DeleteRecord(int position) {
  if (position < 0 || !head) {
    printf("\nError!Such a record does not exist!\n\n");
    return;
  }

  List *tmp = head;

  for (int i = 0; tmp != NULL && i < position; i++) {
    tmp = tmp->next;
  }

  if (tmp == NULL) {
    return;
  }

  if (head == tmp) {
    head = tmp->next;
  }

  if (tmp->next != NULL) {
    tmp->next->prev = tmp->prev;
  }

  if (tmp->prev != NULL) {
    tmp->prev->next = tmp->next;
  }

  printf("\nRecord successfully deleted!\n\n");
  free(tmp);
}

void ShowAllRecords() {
  int number = 0;
  List *tmp = head;

  if (!tmp) {
    printf("\nList is empty!\n\n");
    return;
  }

  while (tmp != NULL) {
    printf("\n");
    printf("record:%d\n", number = number + 1);
    printf("number:%ld\n", tmp->data->number);
    printf("name:%s\n", tmp->data->name);
    printf("surname:%s\n", tmp->data->surname);
    printf("\n");
    tmp = tmp->next;
  }
}