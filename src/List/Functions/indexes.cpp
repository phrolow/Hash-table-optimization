#include "../list.h"

int physindex(list_t *list, int logindex) {
    if(list->happy)
        return logindex + (gethead(list) - 1);

    int pi = 0;

    for(int i = 0; i < logindex; i++) {
        pi = list->next[pi];
    }

    return pi;
}

int getnext(list_t *list, int physindex) {
    if(physindex < 1 || physindex >= list->size)
        return -1;

    return list->next[physindex];
}

int getprev(list_t *list, int physindex) {
    if(physindex < 1 || physindex >= list->size)
        return -1;

    return list->prev[physindex];
}

int isfree(list_t *list, int physindex) {
    if(list->prev[physindex] == -1)
        return 1;

    return 0;
}

int getfree(list_t *list) {
    return list->free;
}

int putfree(list_t *list) {
    int free = 0;

    if(getnext(list, getfree(list)) == 0) {
        resize(list, list->size * 2);
    }

    free = getfree(list);

    list->free = list->next[free];

    return free;
}

int gethead(list_t *list) {
    return list->Head;
}

int gettail(list_t *list) {
    return list->Tail;
}