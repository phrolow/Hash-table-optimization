#ifndef DEBUG_HPP_INCLUDED
#define DEBUG_HPP_INCLUDED

#include <assert.h>
#include <stdio.h>

const size_t FILE_NAME_LEN = 0x20;

const char * const CSV_FORMAT = "data/spreading%d.csv";

void hashTableDetailWordDump(hash_table_t *hashTable, FILE *stream);

void hashTableCsvDump(hash_table_t *hashTable, FILE *stream);

#endif