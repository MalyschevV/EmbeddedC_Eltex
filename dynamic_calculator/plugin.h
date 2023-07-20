#ifndef PLUGIN_H
#define PLUGIN_H

#include <dlfcn.h>
#include <stdio.h>

#define SIZE 127

void PluginLoader(const char *path, const char *name);

#endif