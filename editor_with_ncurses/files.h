#ifndef FILES_H
#define FILES_H

#include <ncurses.h>
#include <stdlib.h>

#define SIZE 127

void ViewFile(const char *file_name);
void EditFile(const char *file_name);
void SaveFile(const char *file_name);

#endif