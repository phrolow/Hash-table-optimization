#include "hashtable_optimization.h"

unsigned int hash1(word_t word) {
    return 1U;
}

unsigned int hashFirstLetter(word_t word) {
    return (int) word[1];
}

unsigned int hashWordLen(word_t word) {
    return strlen(word);
}

unsigned int hashSum(word_t word) {
    int i = 0;
    int sum = 0;

    while(word[i] != '\0') sum += word[i++];

    return sum;
}

unsigned int hashRol(word_t word) {
    unsigned int hash = 0;
    
    size_t len = strlen(word);

    for (size_t i = 0; i < len; ++i)
    {
        hash = ((hash >> 31) | (hash << 1)) xor word[i];
    }

    return hash;
}

unsigned int hashRor(word_t word) {
    unsigned int hash = 0;
    
    size_t len = strlen(word);

    for (size_t i = 0; i < len; ++i)
    {
        hash = ((hash << 31) | (hash >> 1)) xor word[i];
    }

    return hash;
}

unsigned int murmurHash2 (word_t word)
{
    const unsigned int m = 0x5bd1e995;
    const unsigned int seed = 0;
    const int r = 24;

    //unsigned int len = WORLD_LENGTH;
    unsigned int len = strlen(word);
    unsigned int h = seed ^ len;

    const unsigned char * data = (const unsigned char *) word;
    unsigned int k = 0;

    while (len >= 4)
    {
        k  = data[0];
        k |= data[1] << 8;
        k |= data[2] << 16;
        k |= data[3] << 24;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch (len)
    {
        case 3:
        h ^= data[2] << 16;
        case 2:
        h ^= data[1] << 8;
        case 1:
        h ^= data[0];
        h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}