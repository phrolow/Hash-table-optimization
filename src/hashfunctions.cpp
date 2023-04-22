#include "hashtable_optimization.h"

#pragma GCC diagnostic ignored "-Wreturn-type"

unsigned int hash1(word_t word) {
    return 1U;
}

unsigned int hashFirstLetter(word_t word) {
    return (int) word[1];
}

// unsigned int hashWordLen(word_t word) {
//     return strlen(word);
// }

unsigned int hashSum(word_t word) {
    int i = 0;
    int sum = 0;

    while(word[i] != '\0') sum += word[i++];

    return sum;
}

// unsigned int hashRol(word_t word) {
//     unsigned int hash = 0;
    
//     size_t len = strlen(word);

//     for (size_t i = 0; i < len; ++i)
//     {
//         hash = ((hash >> 31) | (hash << 1)) xor word[i];
//     }

//     return hash;
// }

// unsigned int hashRor(word_t word) {
//     unsigned int hash = 0;
    
//     size_t len = strlen(word);

//     for (size_t i = 0; i < len; ++i)
//     {
//         hash = ((hash << 31) | (hash >> 1)) xor word[i];
//     }

//     return hash;
// }

unsigned int murmurHash2 (word_t word) {
    const unsigned seed = 0xeda;
    unsigned len = 0x20;

    const unsigned m = 0x5bd1e995;
    const int r = 24;

    unsigned h = seed ^ len;

    unsigned char * data = (unsigned char *) &word;

    while(len >= 4)
    {
        unsigned k = *((unsigned *) data);

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch(len)
    {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0];
        h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}

// unsigned int simdCrc32(word_t word) {
//     unsigned int hash = 0;

//     union {
//         word_t key;
//         unsigned int blocks[sizeof(word_t) / sizeof(unsigned int)];
//     } cvt;

//     cvt.key = word;

//     for(size_t i = 0; i < sizeof(word_t) / sizeof(unsigned int); i++) {
//         hash = _mm_crc32_u32(hash, cvt.blocks[i]);
//     }
    
//     return hash;
// }

unsigned int simdCrc32(word_t word) {
    asm(
        ".intel_syntax noprefix\n"
        "push    rbp\n"
        "mov     rbp, rsp\n"
        "and     rsp, -32\n"

        "vmovdqa YMMWORD [rsp-64], ymm0\n"    

        "mov     eax, DWORD [rsp - 64]\n"  
                                        
        "crc32d   eax, DWORD [rsp - 60]\n"   
        "crc32d   eax, DWORD [rsp - 56]\n"
        "crc32d   eax, DWORD [rsp - 52]\n"  
        "crc32d   eax, DWORD [rsp - 48]\n" 
        "crc32d   eax, DWORD [rsp - 44]\n"    
        "crc32d   eax, DWORD [rsp - 40]\n"
        "crc32d   eax, DWORD [rsp - 36]\n"   
        
        "mov rsp, rbp\n"
        "pop rbp\n"
        "ret\n"
        ".att_syntax prefix"
    );
}