#include "dirs.h"

int main() {
  WINDOW *first_window, *second_window, *third_window;
  char current_path[MAX_PATH_LENGTH];
  char **dir_contents = NULL;
  char **dir_contents_for_second_window = NULL;
  int count_for_first_window, current_index, ch, windows_flag,
      count_for_second_window, count_tmp;
  initscr();
  int rows, cols;
  getmaxyx(stdscr, rows, cols);
  first_window = newwin(rows - 2, cols / 2, 0, 0);
  second_window = newwin(rows - 2, cols / 2, 0, cols / 2);
  third_window = newwin(rows, cols, rows - 2, 0);
  mvwprintw(third_window, 0, 0,
            "Press F1 - switch directory\t\tPress Tab - open directory\nUP, "
            "DOWN - navigate\t\t\tEsc - exit\n");
  wrefresh(third_window);
  keypad(first_window, TRUE);
  keypad(second_window, TRUE);
  scrollok(first_window, TRUE);
  scrollok(second_window, TRUE);

  dir_contents = (char **)malloc(sizeof(char *) * rows);
  for (int i = 0; i < rows; i++) {
    dir_contents[i] = (char *)malloc(sizeof(char) * MAX_NAME_LENGTH);
  }

  dir_contents_for_second_window = (char **)malloc(sizeof(char *) * rows);
  for (int i = 0; i < rows; i++) {
    dir_contents_for_second_window[i] =
        (char *)malloc(sizeof(char) * MAX_NAME_LENGTH);
  }

  strcpy(current_path, ".");
  count_for_first_window = GetDirectoryContent(current_path, dir_contents);
  count_for_second_window =
      GetDirectoryContent(current_path, dir_contents_for_second_window);

  current_index = 0;
  windows_flag = 1;

  while (1) {
    if (windows_flag) {
      count_tmp = count_for_first_window;
      DrawContents(first_window, dir_contents, count_for_first_window,
                   current_index);
      ch = wgetch(first_window);
    } else {
      count_tmp = count_for_second_window;
      DrawContents(second_window, dir_contents_for_second_window,
                   count_for_second_window, current_index);
      ch = wgetch(second_window);
    }

    if (ch == KEY_UP) {
      current_index--;
      if (current_index < 0) {
        current_index = count_tmp - 1;
      }
    } else if (ch == KEY_DOWN) {
      current_index++;
      if (current_index >= count_tmp) {
        current_index = 0;
      }
    } else if (ch == '\t') {
      if (windows_flag) {
        if (dir_contents[current_index][0] != '.') {
          strcpy(current_path, dir_contents[current_index]);
          count_for_first_window =
              GetDirectoryContent(current_path, dir_contents);
          current_index = 0;
        }
      } else {
        if (dir_contents_for_second_window[current_index][0] != '.') {
          strcpy(current_path, dir_contents_for_second_window[current_index]);
          count_for_second_window =
              GetDirectoryContent(current_path, dir_contents_for_second_window);
          current_index = 0;
        }
      }
    } else if (ch == 27) {
      break;
    } else if (ch == KEY_F(1)) {
      windows_flag = !windows_flag;
    }
  }

  for (int i = 0; i < rows; i++) {
    free(dir_contents[i]);
  }

  for (int i = 0; i < rows; i++) {
    free(dir_contents_for_second_window[i]);
  }

  free(dir_contents);
  free(dir_contents_for_second_window);
  delwin(first_window);
  delwin(second_window);
  delwin(third_window);
  endwin();
  
  return 0;
}