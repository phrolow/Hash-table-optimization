#ifndef HASHTABLE_HPP_INCLUDED
#define HASHTABLE_HPP_INCLUDED

#include <immintrin.h>

typedef __m256i word_t;

#include "../List/list.h"

struct hash_table_t
{
    size_t size;
    list_t **lists;
    unsigned int (*hash)(word_t);
};

const size_t HASH_TABLE_SIZE = 4973;
const size_t POISON = 0xbaadf00dbaadf00d;

hash_table_t *hashTableCtor(size_t size, unsigned int (*hash) (word_t));

void hashTableDtor(hash_table_t *hash_table);

void hashTableAdd(hash_table_t *hash_table, elem_t elem);

int hashTableSearch(hash_table_t *hash_table, elem_t elem);

int hashTableListLength(hash_table_t *hash_table, size_t list_num);

#endif