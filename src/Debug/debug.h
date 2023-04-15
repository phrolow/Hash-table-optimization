#ifndef DEBUG_HPP_INCLUDED
#define DEBUG_HPP_INCLUDED

const size_t FILE_NAME_LEN = 0x20;

const char * const CSV_FILE = "data/spreading.csv";

void hashTableDetailWordDump(hash_table_t *hash_table, FILE *stream);

void hashTableCsvDump(hash_table_t *hash_table, FILE *stream);

#endif