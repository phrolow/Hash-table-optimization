#include "preprocessor.h"

void process(const char *path) {
    FILE *file_pointer = fopen(path, "rb");

    assert(file_pointer);

    struct stat file_stat;

    fstat(fileno(file_pointer), &file_stat);

    size_t file_length = file_stat.st_size;

    char *read_buf = (char *) calloc(sizeof(char), file_length + 1);

    fread(read_buf, sizeof(char), file_length + 1, file_pointer);

    fclose(file_pointer);

    for(int i = 0; i < file_length; i++) {
        if(!isalpha(read_buf[i]))
            read_buf[i] = '\0';
    }

    file_pointer = fopen(path, "wb");

    assert(file_pointer);

    fwrite(read_buf, sizeof(char), file_length, file_pointer);

    fclose(file_pointer);

    free(read_buf);
}