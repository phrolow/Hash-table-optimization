#include "tests.h"

double measureSearch(hash_table_t *hash_table, text_t *text) {
    for(int i = 0; i < NUM_TESTS; i++) {    
        for(size_t j = 0; j < text->num_words; j++) {
            hashTableSearch(hash_table, text->pointers[j]);
        }
    }

    clock_t time_start = clock();

    for(size_t i = 0; i < text->num_words; i++) {
        hashTableSearch(hash_table, text->pointers[i]);
    }

    clock_t time_finish = clock();

    return difftime(time_finish, time_start);
}