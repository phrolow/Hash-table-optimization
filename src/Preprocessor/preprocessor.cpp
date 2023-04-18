#include "preprocessor.hpp"

void process(const char *path) {
    FILE *file_pointer = fopen(path, "rb");

    assert(file_pointer);

    struct stat file_stat;

    fstat(fileno(file_pointer), &file_stat);

    size_t file_length = file_stat.st_size;

    char *read_buf = (char *) calloc(sizeof(char), file_length + 1);

    fread(read_buf, sizeof(char), file_length + 1, file_pointer);

    fclose(file_pointer);

    // for(int i = 0; i < file_length; i++) {
    //     if(!isalpha(read_buf[i]))
    //         read_buf[i] = '\0';
    // }

    size_t num_blocks = 0;

    for(size_t i = 0; i <= file_length; i++) {
        size_t wordLen = 0;

        while(isalpha(read_buf[i])) {
            wordLen++;

            i++;
        }

        num_blocks += ((wordLen + 1) / BLOCK_SIZE + 1) * !!wordLen;
    }

    char *write_buf = (char*) calloc(num_blocks * BLOCK_SIZE, sizeof(char));

    char *write_pointer = write_buf;

    for(size_t i = 0; i <= file_length; i++) {
        size_t inserted = 0;

        while(isalpha(read_buf[i])) {
            *write_pointer = read_buf[i++];

            inserted++;

            write_pointer++;
        }

        if(inserted && !(inserted % 16)) {
            *((size_t*) (write_pointer))     = 0;
            *((size_t*) (write_pointer + 8)) = 0;

            write_pointer += 16;
        }

        while(inserted++ % 16) {
            *write_pointer = '\0';

            write_pointer++;
        }
    }

    file_pointer = fopen(path, "wb");

    assert(file_pointer);

    fwrite(write_buf, sizeof(char), num_blocks * BLOCK_SIZE, file_pointer);

    fclose(file_pointer);

    free(read_buf);
    free(write_buf);
}