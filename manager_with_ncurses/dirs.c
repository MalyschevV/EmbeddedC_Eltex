#include "dirs.h"

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
