#ifndef PREPROCESSOR_HPP_INCLUDED
#define PREPROCESSOR_HPP_INCLUDED

#define DEBUG

#ifdef DEBUG
#include <assert.h>
#endif

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

//const TOKEN_SIZE = 16;

void process(const char *path);

#endif