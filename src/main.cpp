#include "hashtable.hpp"

int main(int argc, char **argv) {
    if(argc == 1) {
        printf("No arguments!\n");

        exit(1);
    }

    char *path = argv[1];

    text_t *words = parse(path);

    unsigned int (*hashes[7])(word_t) = { hash1, hashFirstLetter, hashWordLen, hashSum, hashRol, hashRor, murmurHash2 };

    char file_name[FILE_NAME_LEN];

    for(int i = 0; i < 7; i++) {
        hash_table_t *hasht = hashTableCtor(HASH_TABLE_SIZE, hashes[i]);

        for(int i = 0; i < words->num_words; i++) {
            hashTableAdd(hasht, words->pointers[i]);
        }

        sprintf(file_name, CSV_FORMAT, i);

        FILE *dump = fopen(file_name, "w");

        hashTableCsvDump(hasht, dump);

        fclose(dump);

        hashTableDtor(hasht);
    }
    
    textDtor(words);
}