#include "../hashtable_optimization.h"

text_t *parse(const char *path) {
    FILE *file_pointer = fopen(path, "rb");

    assert(file_pointer);

    struct stat file_stat;

    fstat(fileno(file_pointer), &file_stat);

    size_t file_length = file_stat.st_size;

    char *read_buf = (char *) calloc(sizeof(char), file_length + 1);

    fread(read_buf, sizeof(char), file_length, file_pointer);

    fclose(file_pointer);

    size_t num_words = 1;

    for(int i = 1; i < file_length; i++) {
        if(!read_buf[i - 1] && read_buf[i]) {
            num_words++;
        }
    }

    word_t *pointers = (char **) calloc(sizeof(char*), num_words + 1);

    pointers[0] = read_buf;

    int pointers_index = 0;

    for(int i = 1; i < file_length; i++) {
        if(!read_buf[i - 1] && read_buf[i]) {
            pointers[++pointers_index] = read_buf + i;
        }
    }

    text_t *text_struct = (text_t*) calloc(sizeof(text_t), 1);

    text_struct->text_length = file_length;
    text_struct->text        = read_buf;
    text_struct->num_words   = num_words;
    text_struct->pointers    = pointers;

    return text_struct;
}

void textDtor(text_t *text) {
    text->num_words   = POISON;
    text->text_length = POISON;

    free(text->pointers);
    text->pointers = nullptr;

    free(text->text);
    text->text = nullptr;

    free(text);
}