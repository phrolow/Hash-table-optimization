#include "../list.h"

void ListDelete(list_t *list, int logindex) {
    return ListPhDelete(list, physindex(list, logindex));
}

void ListPhDelete(list_t *list, int physindex) {
    int next = 0,
        prev = 0;

    next = getnext(list, physindex);
    prev = getprev(list, physindex);

    list->next[prev] = next;
    list->prev[physindex] = -1;
    strcpy(list->data[physindex], "\0");
    list->next[physindex] = getfree(list);
    list->prev[next] = prev;

    list->free = physindex;

    list->happy = 0;
}

int ListIndexFirst(list_t *list, elem_t a) {
    int next = 0;

    do {
        next = list->next[next];
    } while(strcmp(list->data[next], a) && next);

    if(next == 0)
        next = -1;

    return next;
}

int ListPhIndexFirst(list_t *list, elem_t a) {
    return physindex(list, ListIndexFirst(list, a));
}

void ListInit(list_t *list) {
    size_t i = 0;

    strcpy(list->data[0], "");
    list->Head = 1;
    list->Tail = 0;

    for(i = 1; i < list->size; i++) {
        strcpy(list->data[i], "");
        list->next[i] = i + 1;
        list->prev[i] = -1;
    }

    list->next[i - 1] = 0;

    list->free = 1;

    list->happy = 1;
}

void resize(list_t *list, size_t newsize) {
    elem_t *newdata = NULL;
    int i = 0,
        next = 0,
        oldsize = 0;

    newdata = (elem_t*)calloc(newsize, sizeof(elem_t));

    strcpy(newdata[0], "");

    do {
        next = list->next[next];
        strcpy(newdata[++i], list->data[next]);
    } while(next);

    oldsize = i;

    list->next = (int*)realloc(list->next, newsize * sizeof(int));
    list->prev = (int*)realloc(list->prev, newsize * sizeof(int));

    list->Head = 1;

    for(i = 1; i < oldsize; i++) {
        list->next[i] = i + 1;
        list->prev[i] = i - 1;
    }

    list->next[--i] = 0;
    list->Tail = i;
    list->free = oldsize;

    for(i = oldsize; i < newsize; i++) {
        strcpy(newdata[i], "");
        list->next[i] = i + 1;
        list->prev[i] = -1;
    }

    list->next[i - 1] = 0;

    list->size = newsize;
    list->happy = 1;
    list->data = newdata;
}