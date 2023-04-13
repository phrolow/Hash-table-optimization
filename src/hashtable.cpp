#include "hashtable.hpp"

hash_table_t *hashTableCtor(size_t size, unsigned int (*hash) (word_t)) {
    hash_table_t *hashTable = (hash_table_t*) calloc(sizeof(hash_table_t), 1);

    hashTable->size  = size;
    hashTable->lists = (list_t**) calloc(sizeof(list_t*), size);
    hashTable->hash  = hash;

    for(size_t i = 0; i < size; i++) {
        hashTable->lists[i] = newList();
    }

    return hashTable;
}

void hashTableDtor(hash_table_t *hashTable) {
    for(size_t i = 0; i < hashTable->size; i++) {
        ListDtor(hashTable->lists[i]);

        hashTable->lists[i] = nullptr;
    }

    hashTable->size = POISON;

    free(hashTable->lists);
    hashTable->lists = nullptr;
    hashTable->hash = nullptr;
    
    free(hashTable);
}

void hashTableAdd(hash_table_t *hashTable, elem_t elem) {
    unsigned int list_num = hashTable->hash(elem);

    ListTailInsert(hashTable->lists[list_num], elem);
}

int hashTableSearch(hash_table_t *hashTable, elem_t elem) {
    unsigned int list_num = hashTable->hash(elem);

    return ListIndexFirst(hashTable->lists[list_num], elem);
}

int hashTableListLength(hash_table_t *hashTable, size_t list_num) {
    return gettail(hashTable->lists[list_num]);
}