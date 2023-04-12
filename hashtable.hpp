#ifndef HASHTABLE_HPP_INCLUDED
#define HASHTABLE_HPP_INCLUDED

typedef char word_t[WORLD_LENGTH];

#include "List/list.h"

const size_t POISON = 0xbaadf00dbaadf00d;
struct hash_table_t
{
    size_t size;
    list_t *lists;
    unsigned int (*hash) (word_t);
};

unsigned int hash1(word_t word);

unsigned int hashFirstLetter(word_t word);

unsigned int hashWordLen(word_t word);

unsigned int hashSum(word_t word);

unsigned int hashRol(word_t word);

unsigned int hashRor(word_t word);

unsigned int murmurHash2(word_t word);

#endif