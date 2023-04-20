#include "../hashtable_optimization.h"

// void hashTableDetailWordDump(hash_table_t *hash_table, FILE *stream) {
//     fprintf(stream, "Hash table dump:\n");

//     for(int i = 0; i < hash_table->size; i++) {
//         fprintf(stream, "\t[%d]: ", i);

//         list_t *list = hash_table->lists[i];

//         int list_index = gethead(list);

//         do {
//             fprintf(stream, "%s, ", (char*) list->data[list_index]);

//             list_index = getnext(list, list_index);
//         } while(list->data[list_index]);

//         fprintf(stream, "\n");
//     }

//     fprintf(stream, "\n");
// }

void hashTableCsvDump(hash_table_t *hash_table, FILE *stream) {
    for(int i = 0; i < hash_table->size; i++) {
        list_t *list = hash_table->lists[i];

        int list_index = gethead(list);

        list_index = getnext(list, list_index);

        size_t num_words = 0;

        int zero = _mm256_movemask_epi8(_mm256_cmpeq_epi64(_mm256_setzero_si256(), list->data[list_index]));

        while(zero != -1 && list_index){
        //while(list_index) {
            //printf("%s\n", (char*) list->data + list_index);
            num_words++;

            list_index = getnext(list, list_index);

            zero = _mm256_movemask_epi8(_mm256_cmpeq_epi64(_mm256_setzero_si256(), list->data[list_index]));
        }

        fprintf(stream, "%lu\t", num_words);
    }

    fprintf(stream, "\n");
}