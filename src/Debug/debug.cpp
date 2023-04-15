#include "../hashtable_optimization.h"

void hashTableDetailWordDump(hash_table_t *hash_table, FILE *stream) {
    fprintf(stream, "Hash table dump:\n");

    for(int i = 0; i < hash_table->size; i++) {
        fprintf(stream, "\t[%d]: ", i);

        list_t *list = hash_table->lists[i];

        int list_index = gethead(list);

        do {
            fprintf(stream, "%s, ", list->data[list_index]);

            list_index = getnext(list, list_index);
        } while(list->data[list_index]);

        fprintf(stream, "\n");
    }

    fprintf(stream, "\n");
}

void hashTableCsvDump(hash_table_t *hash_table, FILE *stream) {
    for(int i = 0; i < hash_table->size; i++) {
        list_t *list = hash_table->lists[i];

        int list_index = gethead(list);

        size_t num_words = 0;

        // do {
        //     ++num_words;

        //     list_index = getnext(list, list_index);
        // } while(list->data[list_index]);

        while(list->data[list_index]) {
            num_words++;

            list_index = getnext(list, list_index);
        }

        fprintf(stream, "%lu\t", num_words);
    }

    fprintf(stream, "\n");
}