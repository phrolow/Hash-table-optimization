#include "hashtable.hpp"

void hashTableCtor(hash_table_t *hashTable, size_t size, unsigned int (*hash) (word_t)) {
    hashTable = (hash_table_t*) calloc(sizeof(hash_table_t), 1);

    hashTable->size  = size;
    hashTable->lists = (list_t*) calloc(sizeof(hash_table_t), size);
    hashTable->hash  = hash;
}

void hashTableDtor(hash_table_t *hashTable) {
    hashTable->size = POISON;
    free(hashTable->lists);
    hashTable->hash = nullptr;

    free(hashTable);
}

void hashTableAdd(hash_table_t *hashTable, elem_t elem) {
    unsigned int list_num = hashTable->hash(elem);

    ListTailInsert(hashTable->lists + list_num, elem);
}

int hashTableSearch(hash_table_t *hashTable, elem_t elem) {
    unsigned int list_num = hashTable->hash(elem);

    return ListIndexFirst(hashTable->lists + list_num, elem);
}