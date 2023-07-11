#include <ncurses.h>
#include <stdlib.h>
#define SIZE 127

void ViewFile(const char *file_name) {
  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    printw("Failed to open file\n");
    return;
  }
  clear();
  int ch;
  while ((ch = fgetc(file)) != EOF) {
    printw("%c", ch);
  }
  refresh();
  fclose(file);
  printw("\nPress any key...");
  getch();
}

void EditFile(const char *file_name) {
  FILE *file = fopen(file_name, "r+");
  if (file == NULL) {
    printw("Failed to open file\n");
    return;
  }
  clear();
  keypad(stdscr, TRUE);
  int ch, prev_ch;
  while ((ch = getch()) != KEY_F(2)) {
    if (ch == KEY_DC) {
      prev_ch = ftell(file);
      fseek(file, prev_ch, SEEK_SET);
      fputc(' ', file);
      move(prev_ch / COLS, prev_ch % COLS);
      refresh();
    } else if (ch != ERR) {
      prev_ch = ftell(file);
      fputc(ch, file);
      refresh();
      prev_ch++;
    }
  }
  fclose(file);
  printw("\nPress any key...");
  getch();
}

void SaveFile(const char *file_name) {
  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    printw("Failed to open file.\n");
    return;
  }
  FILE *temp = tmpfile();
  if (temp == NULL) {
    printw("Failed to open tepm file.\n");
    fclose(file);
    return;
  }
  int ch;
  while ((ch = fgetc(file)) != EOF) {
    fputc(ch, temp);
  }
  fclose(file);
  file = fopen(file_name, "w");
  if (file == NULL) {
    printw("Failed to save file.\n");
    fclose(temp);
    return;
  }
  fseek(temp, 0, SEEK_SET);
  while ((ch = fgetc(temp)) != EOF) {
    fputc(ch, file);
  }
  fclose(temp);
  fclose(file);
  printw("File saved!\n");
  printw("Press any key...");
  getch();
}

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