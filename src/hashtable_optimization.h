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
    register unsigned int hash  asm ("eax") = 0;
    register word_t       *ptr  asm ("r8")  = word;

    asm(
        ".intel_syntax noprefix\n"

        "xor rax, rax\n"

        "mov      eax, DWORD [r8]\n"  
                                        
        "crc32d   eax, DWORD [r8 - 4]\n"   
        "crc32d   eax, DWORD [r8 - 8]\n"
        "crc32d   eax, DWORD [r8 - 12]\n"  
        "crc32d   eax, DWORD [r8 - 16]\n" 
        "crc32d   eax, DWORD [r8 - 20]\n"    
        "crc32d   eax, DWORD [r8 - 24]\n"
        "crc32d   eax, DWORD [r8 - 28]\n"   

        ".att_syntax prefix"
        : "=r" (hash)
        : "r" (ptr)
    );

    return hash;
}

#ifdef DEBUG

#include "Debug/debug.h"

#endif

#endif