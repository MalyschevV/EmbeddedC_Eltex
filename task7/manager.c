#include <dirent.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PATH_LENGTH 256
#define MAX_NAME_LENGTH 128

int GetDirectoryContent(const char *path, char **dir_contents) {
  DIR *dir;
  struct dirent *entry;
  int count_for_first_window = 0;
  dir = opendir(path);
  if (dir == NULL) {
    return -1;
  }
  while ((entry = readdir(dir)) != NULL) {
    strcpy(dir_contents[count_for_first_window], entry->d_name);
    count_for_first_window++;
  }
  closedir(dir);
  return count_for_first_window;
}

void DrawContents(WINDOW *win, char **dir_contents, int count_for_first_window,
                   int current_index) {
  werase(win);
  for (int i = 0; i < count_for_first_window; i++) {
    if (i == current_index) {
      wattron(win, A_REVERSE);
    }
    mvwprintw(win, i, 0, "%s", dir_contents[i]);
    if (i == current_index) {
      wattroff(win, A_REVERSE);
    }
  }
  wrefresh(win);
}

int main() {
  WINDOW *first_window, *second_window;
  char current_path[MAX_PATH_LENGTH];
  char **dir_contents = NULL;
  char **dir_contents_for_second_window = NULL;
  int count_for_first_window, current_index, ch, windows_flag, count_for_second_window, count_tmp;
  initscr();
  int rows, cols;
  getmaxyx(stdscr, rows, cols);
  first_window = newwin(rows, cols / 2, 0, 0);
  second_window = newwin(rows, cols / 2, 0, cols / 2);
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
    dir_contents_for_second_window[i] = (char *)malloc(sizeof(char) * MAX_NAME_LENGTH);
  }
  strcpy(current_path, ".");
  count_for_first_window = GetDirectoryContent(current_path, dir_contents);
  count_for_second_window = GetDirectoryContent(current_path, dir_contents_for_second_window);
  current_index = 0;
  windows_flag = 1;
  while (1) {
    if (windows_flag) {
      count_tmp = count_for_first_window;
      DrawContents(first_window, dir_contents, count_for_first_window, current_index);
      ch = wgetch(first_window);
    } else {
      count_tmp = count_for_second_window;
      DrawContents(second_window, dir_contents_for_second_window, count_for_second_window, current_index);
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
    }
    else if (ch == '\t') {
      if (windows_flag) {
        if (dir_contents[current_index][0] != '.') {
          strcpy(current_path, dir_contents[current_index]);
          count_for_first_window = GetDirectoryContent(current_path, dir_contents);
          current_index = 0;
        }
      } else {
        if (dir_contents_for_second_window[current_index][0] != '.') {
          strcpy(current_path, dir_contents_for_second_window[current_index]);
          count_for_second_window = GetDirectoryContent(current_path, dir_contents_for_second_window);
          current_index = 0;
        }
      }
    }
    else if (ch == 27) {
      break;
    }
    else if (ch == KEY_F(1)) {
      windows_flag = !windows_flag;
    }
  }
  for (int i = 0; i < rows; i++) {
    free(dir_contents[i]);
  }
  for(int i = 0; i < rows; i++){
    free(dir_contents_for_second_window[i]);
  }
  free(dir_contents);
  free(dir_contents_for_second_window);
  delwin(first_window);
  delwin(second_window);
  endwin();
  return 0;
}