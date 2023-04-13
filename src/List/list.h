#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

//#define DEBUG

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _LOCATION_ __PRETTY_FUNCTION__, __FILE__, __LINE__
#define Head next[0]
#define Tail prev[0]

#define CHECK(cond, err) (cond) ? 0 : (err)

#define newList() newList_(_LOCATION_)

typedef char* elem_t;

typedef int err_t;

typedef struct ListInfo {
    const char  *func,
                *file;
    size_t line;
} listinfo;

typedef struct List {
    elem_t  *data;
    int  *next,
            *prev;
    size_t size;
    int happy,
        free;
    listinfo info;
} list_t;

const size_t DEFAULTSIZE = 0x40;
const size_t WORLD_LENGTH = 0x10;

void add(list_t *q, elem_t a);

elem_t get(list_t *q);

void resize(list_t *list, size_t newSize);

void del(list_t *q, int num);

void insert(list_t *q, elem_t a, int num);

list_t *newList_(const char* func, const char* file, size_t line);

void ListDtor(list_t *list);

void ListDump_(struct List *list, const char *func, const char *file, size_t line);

void ListGraphDump(list_t *list);

err_t ListCheck_(struct List *list, const char* func, const char* file, size_t line);

int physindex(list_t *list, int logindex);

int getprev(list_t *list, int physindex);

int getnext(list_t *list, int physindex);

int isfree(list_t *list, int physindex);

int getfree(list_t *list);

int putfree(list_t *list);

int gethead(list_t *list);

int gettail(list_t *list);

elem_t *ListFirst(list_t *list);

elem_t *ListLast(list_t *list);

elem_t *ListNext(list_t *list);

elem_t *ListPrev(list_t *list);

void ListHeadInsert(list_t *list, elem_t a);

void ListTailInsert(list_t *list, elem_t a);

void ListInsertAfter(list_t *list, elem_t a, int logindex);

void ListInsertBefore(list_t *list, elem_t a, int logindex);

void ListPhInsertAfter(list_t *list, elem_t a, int physindex);

void ListPhInsertBefore(list_t *list, elem_t a, int physindex);

void ListDelete(list_t *list, int logindex);

void ListPhDelete(list_t *list, int physindex);

int ListIndexFirst(list_t *list, elem_t a);

int ListPhIndexFirst(list_t *list, elem_t a);

void ListInit(list_t *list);

#endif