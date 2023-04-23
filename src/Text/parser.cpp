#include "../hashtable_optimization.h"

#pragma GCC diagnostic ignored "-Wunused-result"

text_t *parse(const char *path) {
    FILE *file_pointer = fopen(path, "rb");

    assert(file_pointer);

    struct stat file_stat;

    fstat(fileno(file_pointer), &file_stat);

    size_t file_length = file_stat.st_size;

    //char *read_buf = (char *) calloc(sizeof(char), file_length + 1);
    char *read_buf = (char*)aligned_alloc(DATA_ALIGNMENT, sizeof(char) * (file_length + 32));

    memset(read_buf, 0, sizeof(elem_t) * DEFAULTSIZE);

    fread(read_buf, sizeof(char), file_length, file_pointer);

    fclose(file_pointer);

    size_t num_words = 1;

    for(int i = 1; i < file_length; i++) {
        if(!read_buf[i - 1] && read_buf[i]) {
            num_words++;
        }
    }

    // word_t *pointers = (word_t *) calloc(sizeof(word_t), num_words + 1);

    // pointers[0] = read_buf;

    // int pointers_index = 0;

    // for(int i = 1; i < file_length; i++) {
    //     if(!read_buf[i - 1] && read_buf[i]) {
    //         pointers[++pointers_index] = read_buf + i;
    //     }
    // }
    


    // words[0] = _mm256_load_si256((word_t*) read_buf);

    // printf("Anton\n");

    // for(int i = 0; i < file_length / sizeof(word_t); i++) {
    //     words[i] = _mm256_load_si256((word_t*) (read_buf + i * sizeof(word_t)));
    // }

    text_t *text_struct = (text_t*) calloc(sizeof(text_t), 1);

    text_struct->text_length = file_length;
    text_struct->text        = read_buf;
    text_struct->num_words   = num_words;
    // text_struct->words       = words;
    text_struct->words       = (word_t *) read_buf;

    return text_struct;
}

void textDtor(text_t *text) {
    text->num_words   = POISON;
    text->text_length = POISON;

    // free(text->words);
    text->words = nullptr;

    free(text->text);
    text->text = nullptr;

    free(text);
}