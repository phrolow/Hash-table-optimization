#ifndef TEXT_HPP_INCLUDED
#define TEXT_HPP_INCLUDED

#include "../HashTable/hashtable.h"

#include <sys/stat.h>

struct text_t {
    size_t text_length;
    char *text;
    size_t num_words;
    word_t *pointers;
};

text_t *parse(const char *path);

void textDtor(text_t *text);

#endif