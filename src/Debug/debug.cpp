#include "../hashtable.hpp"

void hashTableDetailWordDump(hash_table_t *hashTable, FILE *stream) {
    fprintf(stream, "Hash table dump:\n");

    for(int i = 0; i < hashTable->size; i++) {
        fprintf(stream, "\t[%d]: ", i);

        list_t *list = hashTable->lists[i];

        int list_index = gethead(list);

        do {
            fprintf(stream, "%s, ", list->data[list_index]);

            list_index = getnext(list, list_index);
        } while(list->data[list_index]);

        fprintf(stream, "\n");
    }

    fprintf(stream, "\n");
}

void hashTableCsvDump(hash_table_t *hashTable, FILE *stream) {
    for(int i = 0; i < hashTable->size; i++) {
        list_t *list = hashTable->lists[i];

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