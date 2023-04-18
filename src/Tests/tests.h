#ifndef TESTS_HPP_INCLUDED
#define TESTS_HPP_INCLUDED

#include <time.h>

#include "../HashTable/hashtable.h"
#include "../Text/text.h"

const int NUM_TESTS = 1000;

double measureSearch(hash_table_t *hash_table, text_t *text);

#endif