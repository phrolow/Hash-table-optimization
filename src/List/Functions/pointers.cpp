#include "../list.h"

elem_t *ListFirst(list_t *list) {
    return list->data + gethead(list);
}

elem_t *ListLast(list_t *list) {
    return list->data + gettail(list);
}

elem_t *ListNext(list_t *list, int physindex) {
    return list->data + getnext(list, physindex);
}

elem_t *ListPrev(list_t *list, int physindex) {
    return list->data + getprev(list, physindex);
}

