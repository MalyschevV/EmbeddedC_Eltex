#include "phonebook.h"

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
  return 0;
}