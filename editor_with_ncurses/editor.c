#include "files.h"

int main() {
  char file_name[SIZE];
  int choice;

  initscr();
  printw("enter file name: ");
  scanw("%s", file_name);
  
  while (1) {
    clear();
    printw("1.Open file\n2.Edit file\n3.Save file\n4.Exit\n");
    printw("choice: ");
    refresh();
    scanw("%d", &choice);

    switch (choice) {

      case 1:
        ViewFile(file_name);
        break;
      
      case 2:
        EditFile(file_name);
        break;
      
      case 3:
        SaveFile(file_name);
        break;
      
      case 4:
        endwin();
        return 0;
      
      default:
        printw("Error choice\n");
        break;
    }
  }
}