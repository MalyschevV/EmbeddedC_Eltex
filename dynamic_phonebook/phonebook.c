#include <malloc.h>
#include <stdio.h>
#define BUFFER 12

typedef struct Phonebook {
  long number;
  char name[BUFFER];
  char surname[BUFFER];
} Phonebook;

typedef struct List {
  Phonebook *data;
  struct List *next;
  struct List *prev;
} List;

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

int main() {
  int choice = 0;
  int position = 0;
  long key = 0;
  Phonebook phonebook;
  while (1) {
    printf(
        "press 1 to show entire phonebook.\npress 2 to add to phonebook."
        "\npress 3 to search in phonebook.\npress 4 to delete in "
        "phonebook.\npress 5 to exit.\n");
    scanf("%d", &choice);
    switch (choice) {
      case 1:
        ShowAllRecords();
        break;
      case 2:
        printf("\n");
        printf("Enter a number:");
        scanf("%ld", &phonebook.number);
        printf("Enter a name:");
        scanf("%s", phonebook.name);
        printf("Enter a surname:");
        scanf("%s", phonebook.surname);
        printf("\n");
        InsertRecord(CreateNewRecord(&phonebook));
        break;
      case 3:
        printf("\n");
        printf("Enter a number for search:");
        scanf("%ld", &key);
        SearchRecordByNumber(key);
      case 4:
        printf("\n");
        printf("Enter a position for delete:");
        scanf("%d", &position);
        DeleteRecord(position - 1);
        break;
      case 5:
        return 0;
      default:
        break;
    }
  }
}
