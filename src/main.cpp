#include "hashtable.hpp"

int main(int argc, char **argv) {
    if(argc == 1) {
        printf("No arguments!\n");

        exit(1);
    }

    char *path = argv[1];

    text_t *words = parse(path);

    unsigned int (*hashes[7])(word_t) = { hash1, hashFirstLetter, hashWordLen, hashSum, hashRol, hashRor, murmurHash2 };

    hash_table_t *hasht1 = hashTableCtor(HASH_TABLE_SIZE, hash1);

    for(int i = 0; i < words->num_words; i++) {
        hashTableAdd(hasht1, words->pointers[i]);
    }

    hashTableDump(hasht1, stdout);

    hashTableDtor(hasht1);
    
    textDtor(words);
}