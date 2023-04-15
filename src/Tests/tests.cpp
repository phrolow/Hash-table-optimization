#include "tests.h"

double measureSearch(hash_table_t *hash_table, text_t *text) {
    clock_t time_start = clock();

    for(size_t i = 0; i < text->num_words; i++) {
        hashTableSearch(hash_table, text->pointers[i]);
    }

    clock_t time_finish = clock();

    return difftime(time_finish, time_start);
}