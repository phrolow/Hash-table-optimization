#include "../list.h"

list_t *newList_(const char* func, const char* file, size_t line) {
    int i = 0;

    listinfo new_info = { NULL, NULL, 0 };
//    list list = { NULL, NULL, NULL, 0, 0, 0, info };

//    listinfo *new_info = (listinfo*) malloc(sizeof(listinfo));
    list_t *new_list = (list_t*) malloc(sizeof(list_t));

    new_list->size = DEFAULTSIZE;

    // new_list->data = (elem_t*)calloc(new_list->size, sizeof(elem_t));
    new_list->data = (elem_t*)aligned_alloc(DATA_ALIGNMENT, sizeof(elem_t) * DEFAULTSIZE);

    memset(new_list->data, 0, sizeof(elem_t) * DEFAULTSIZE);

    new_list->next = (int*)calloc(new_list->size, sizeof(int));
    new_list->prev = (int*)calloc(new_list->size, sizeof(int));

    new_info.func = func;
    new_info.file = file;
    new_info.line = line;

    new_list->info = new_info;

    ListInit(new_list);

    return new_list;
}

void ListDtor(list_t *list) {
    for(int i = 0; i < list->size; i++)
        list->data[i] = _mm256_setzero_si256();;

    list->size = 0;
    list->Head = 0;
    list->Tail = 0;

    free(list->data);
    free(list->next);
    free(list->prev);

    free(list);

    return;
}