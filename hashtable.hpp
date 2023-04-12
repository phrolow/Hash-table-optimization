#ifndef HASHTABLE_HPP_INCLUDED
#define HASHTABLE_HPP_INCLUDED

#define DEBUG

typedef char* word_t;

#include "List/list.h"
#include "Text/text.hpp"

const size_t HASH_TABLE_SIZE = 10;
const size_t POISON = 0xbaadf00dbaadf00d;
struct hash_table_t
{
    size_t size;
    list_t **lists;
    unsigned int (*hash) (word_t);
};

unsigned int hash1(word_t word);

unsigned int hashFirstLetter(word_t word);

unsigned int hashWordLen(word_t word);

unsigned int hashSum(word_t word);

unsigned int hashRol(word_t word);

unsigned int hashRor(word_t word);

unsigned int murmurHash2(word_t word);

hash_table_t *hashTableCtor(size_t size, unsigned int (*hash) (word_t));

void hashTableDtor(hash_table_t *hashTable);

void hashTableAdd(hash_table_t *hashTable, elem_t elem);

int hashTableSearch(hash_table_t *hashTable, elem_t elem);

int hashTableListLength(hash_table_t *hashTable, size_t list_num);

#ifdef DEBUG

#include "Debug/debug.hpp"

#endif

#endif