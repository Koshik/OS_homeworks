#ifndef HELPERS_H
#define HELPERS_H

#include <unistd.h>
#include <stdlib.h>

ssize_t write_(int, const void*, size_t);

ssize_t read_(int, void*, size_t);

ssize_t read_until(int, void*, size_t, char);

int spawn(const char *, char * const *);

#endif
