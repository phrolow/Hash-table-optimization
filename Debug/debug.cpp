#include "../hashtable.hpp"

void hashTableDump(hash_table_t *hashTable, FILE *stream) {
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