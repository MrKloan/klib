#ifndef KLIB_LIST_H
#define KLIB_LIST_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct ListItem {
    void *value;
    struct ListItem *next;
} ListItem;

typedef struct List {
    ListItem *element;
    size_t size;

    boolean (*add)(struct List*, void*, size_t, boolean);
    boolean (*remove)(struct List*, size_t);
    boolean (*swap)(struct List*, size_t, size_t);
    
    size_t (*count)(struct List*);
    void *(*get)(struct List*, size_t);
    ListItem *(*getItem)(struct List*, size_t);
    ListItem *(*getLast)(struct List*);

    void (*clear)(struct List*);
    void (*free)(struct List*);
} List;

List* libexp ListNew(void);
void libexp ListInit(List*);
void libexp ListFree(List*);
void libexp ListClear(List*);

boolean libexp ListAdd(List*, void*, size_t, boolean);
boolean libexp ListRemove(List*, size_t);
boolean libexp ListSwap(List*, size_t, size_t);

size_t libexp ListCount(List*);
void* libexp ListGet(List*, size_t);
ListItem* libexp ListGetItem(List*, size_t);
ListItem* libexp ListGetLast(List*);

#ifdef	__cplusplus
}
#endif

#endif /* KLIB_LIST_H */
