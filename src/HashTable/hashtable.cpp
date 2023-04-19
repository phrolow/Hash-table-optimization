#include "hashtable.h"

hash_table_t *hashTableCtor(size_t size, unsigned int (*hash) (word_t)) {
    hash_table_t *hash_table = (hash_table_t*) calloc(sizeof(hash_table_t), 1);

    hash_table->size  = size;
    hash_table->lists = (list_t**) calloc(sizeof(list_t*), size);
    hash_table->hash  = hash;

    for(size_t i = 0; i < size; i++) {
        hash_table->lists[i] = newList();
    }

    return hash_table;
}

void hashTableDtor(hash_table_t *hash_table) {
    for(size_t i = 0; i < hash_table->size; i++) {
        ListDtor(hash_table->lists[i]);

        hash_table->lists[i] = nullptr;
    }

    hash_table->size = POISON;

    free(hash_table->lists);
    hash_table->lists = nullptr;
    hash_table->hash = nullptr;
    
    free(hash_table);
}

void hashTableAdd(hash_table_t *hash_table, elem_t elem) {
    unsigned int list_num = hash_table->hash(elem) % HASH_TABLE_SIZE;

    if(ListIndexFirst(hash_table->lists[list_num], elem) == -1) {
        ListTailInsert(hash_table->lists[list_num], elem);
    }
}

int hashTableSearch(hash_table_t *hash_table, elem_t elem) {
    unsigned int list_num = hash_table->hash(elem) % HASH_TABLE_SIZE;

    return ListIndexFirst(hash_table->lists[list_num], elem);
}

int hashTableListLength(hash_table_t *hash_table, size_t list_num) {
    return gettail(hash_table->lists[list_num]);
}