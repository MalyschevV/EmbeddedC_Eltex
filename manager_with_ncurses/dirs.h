#ifndef DIRS_H
#define DIRS_H

#include <dirent.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 256
#define MAX_NAME_LENGTH 128

int GetDirectoryContent(const char *path, char **dir_contents);
void DrawContents(WINDOW *win, char **dir_contents, int count_for_first_window,
                  int current_index);

#endif
