#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <malloc.h>
#include <stdio.h>

#define BUFFER 12
#define MSG_SIZE 1024

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

List *CreateNewRecord(Phonebook *phonebook);
void InsertRecord(List *list);
void SearchRecordByNumber(long key);
void DeleteRecord(int position);
void ShowAllRecords();

#endif