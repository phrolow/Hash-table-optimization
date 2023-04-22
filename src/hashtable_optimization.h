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

unsigned int simdCrc32(word_t word);

#ifdef DEBUG

#include "Debug/debug.h"

#endif

#endif