#include "hashtable_optimization.h"

int main(int argc, char **argv) {
    if(argc == 1) {
        printf("No arguments!\n");

        exit(1);
    }

    char *path = argv[1];

    text_t *words = parse(path);

    FILE *dump = fopen(CSV_FILE, "w");

    hash_table_t *hasht = hashTableCtor(HASH_TABLE_SIZE);

    for(int i = 0; i < words->num_words; i++) {
        hashTableAdd(hasht, words->words + i);
    }

    hashTableCsvDump(hasht, dump);

    double search_time = measureSearch(hasht, words) / CLOCKS_PER_SEC;

    printf("%lg s\n", search_time);

    hashTableDtor(hasht);
    
    fclose(dump);
    
    textDtor(words);
}