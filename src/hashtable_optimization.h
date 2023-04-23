#ifndef HASHTABLE_OPTIMIZATION_HPP_INCLUDED
#define HASHTABLE_OPTIMIZATION_HPP_INCLUDED

#define DEBUG

#include "List/list.h"
#include "Text/text.h"
#include "HashTable/hashtable.h"
#include "Tests/tests.h"

//extern "C" unsigned int _simdCrc32(word_t word);

unsigned int hash1(word_t word);

unsigned int hashFirstLetter(word_t word);

unsigned int hashWordLen(word_t word);

unsigned int hashSum(word_t word);

unsigned int hashRol(word_t word);

unsigned int hashRor(word_t word);

unsigned int murmurHash2(word_t word);

inline __attribute__((always_inline)) unsigned int simdCrc32(word_t *word) {
    unsigned int hash = 0;

    asm(
        ".intel_syntax noprefix\n"

        "xor rax, rax\n"

        "mov      eax, DWORD [rdi]\n"  
                                        
        "crc32d   eax, DWORD [rdi - 4]\n"   
        "crc32d   eax, DWORD [rdi - 8]\n"
        "crc32d   eax, DWORD [rdi - 12]\n"  
        "crc32d   eax, DWORD [rdi - 16]\n" 
        "crc32d   eax, DWORD [rdi - 20]\n"    
        "crc32d   eax, DWORD [rdi - 24]\n"
        "crc32d   eax, DWORD [rdi - 28]\n"   

        ".att_syntax prefix"
        : "=a" (hash)
        : "D" (word)
    );

    // union {
    //     word_t key;
    //     unsigned int blocks[sizeof(word_t) / sizeof(unsigned int)];
    // } cvt;

    // cvt.key = *word;

    // for(size_t i = 0; i < sizeof(word_t) / sizeof(unsigned int); i++) {
    //     hash = _mm_crc32_u32(hash, cvt.blocks[i]);
    // }

    // asm {
    //     "movl -64(%1)"
    // }

    return hash;
}

#ifdef DEBUG

#include "Debug/debug.h"

#endif

#endif