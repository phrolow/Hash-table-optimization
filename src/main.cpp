#include "hashtable_optimization.h"

int main(int argc, char **argv) {
    if(argc == 1) {
        printf("No arguments!\n");

        exit(1);
    }

    char *path = argv[1];

    text_t *words = parse(path);

    unsigned int (*hashes[7])(word_t) = { hash1, hashFirstLetter, hashWordLen, hashSum, hashRol, hashRor, murmurHash2 };

    FILE *dump = fopen(CSV_FILE, "w");

    for(int i = 0; i < 7; i++) {
        hash_table_t *hasht = hashTableCtor(HASH_TABLE_SIZE, hashes[i]);

        for(int i = 0; i < words->num_words; i++) {
            hashTableAdd(hasht, words->pointers[i]);
        }

        hashTableCsvDump(hasht, dump);

        measureSearch(hasht, words);
        measureSearch(hasht, words);

        double search_time = measureSearch(hasht, words) / CLOCKS_PER_SEC;

        printf("%d: %lg s\n", i + 1, search_time);

        hashTableDtor(hasht);
    }

    fclose(dump);
    
    textDtor(words);
}