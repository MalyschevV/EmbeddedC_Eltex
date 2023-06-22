#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER 127
#define RECORDS 10
#define NULLVALUE 0

struct Phonebook {
  long number;
  char *name;
  char *surname;
};

void ShowAllRecords(struct Phonebook *phonebook, int size) {
  int number = 0;
  if (phonebook[0].number == NULLVALUE) {
    printf("\nPhonebook is empty!\n\n");
  }
  for (int i = 0; i < size; i++) {
    if (phonebook[i].number != NULLVALUE) {
      printf("\n");
      printf("record:%d\n", number = number + 1);
      printf("number: %ld\n", phonebook[i].number);
      printf("name: %s\n", phonebook[i].name);
      printf("surname: %s\n", phonebook[i].surname);
      printf("\n");
    }
  }
}

int SearchRecordByNumber(struct Phonebook *phonebook, int size, long key) {
  if (key == NULLVALUE) {
    return -1;
  }
  for (int i = 0; i < size; i++) {
    if (phonebook[i].number == key) {
      return i;
    }
  }
  return -1;
}

int AddRecord(struct Phonebook *phonebook, int size, long new_number,
              char *new_name, char *new_surname) {
  if (phonebook[size - 1].number != NULLVALUE) {
    printf("\nError! Phonebook is full!\n\n");
    return -1;
  }
  if (new_number == NULLVALUE) {
    printf("\nError! Bad value for number!\n\n");
    return -1;
  }
  for (int i = 0; i < size; i++) {
    if (phonebook[i].number == NULLVALUE) {
      phonebook[i].name = (char *)malloc(BUFFER);
      phonebook[i].surname = (char *)malloc(BUFFER);
      phonebook[i].number = new_number;
      strcpy(phonebook[i].name, new_name);
      strcpy(phonebook[i].surname, new_surname);
      break;
    }
  }
  return 0;
}

int DeleteRecord(struct Phonebook *phonebook, int size, long deleted_number) {
  for (int i = 0; i < size; i++) {
    if (phonebook[i].number == deleted_number) {
      phonebook[i].number = NULLVALUE;
      phonebook[i].name = "empty";
      phonebook[i].surname = "empty";
      return 0;
    }
  }
  printf("\nError!Such a record does not exist!\n\n");
  return -1;
}

int main() {
  struct Phonebook phonebook[RECORDS] = {};
  int choice, result = 0;
  long key, new_number_value = 0;
  char new_name_value[BUFFER], new_surname_value[BUFFER];
  while (1) {
    printf("press 1 to show entire phonebook.\npress 2 to search in "
           "phonebook.\npress 3 to add to phonebook.\npress 4 to delete in "
           "phonebook.\npress 5 to exit.\n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      ShowAllRecords(phonebook, RECORDS);
      break;
    case 2:
      printf("Enter a number:\n");
      scanf("%ld", &key);
      result = SearchRecordByNumber(phonebook, RECORDS, key);
      if (result != -1) {
        printf("\nfound record!\n");
        printf("number: %ld\n", phonebook[result].number);
        printf("name: %s\n", phonebook[result].name);
        printf("surname: %s\n", phonebook[result].surname);
        printf("\n");
      } else {
        printf("\nError! wrong record!\n\n");
      }
      break;
    case 3:
      printf("Enter a new number:\n");
      scanf("%ld", &new_number_value);
      printf("Enter a new name:\n");
      scanf("%s", new_name_value);
      printf("Enter a new surname:\n");
      scanf("%s", new_surname_value);
      if (AddRecord(phonebook, RECORDS, new_number_value, new_name_value,
                    new_surname_value) != -1) {
        printf("\nRecord successfully added!\n\n");
      }
      break;
    case 4:
      printf("Enter a number:\n");
      scanf("%ld", &key);
      if (DeleteRecord(phonebook, RECORDS, key) == 0) {
        printf("\nRecord successfully deleted!\n\n");
      }
      break;
    case 5:
      return 0;
    default:
      break;
    }
  }
  return 0;
}
