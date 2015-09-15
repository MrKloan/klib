#ifndef KLIB_ARRAY_H
#define KLIB_ARRAY_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct Array {
    void **element;
    size_t size;

    boolean (*add)(struct Array*, void*, size_t, boolean);
    boolean (*remove)(struct Array*, size_t);
    boolean (*swap)(struct Array*, size_t, size_t);
    void *(*get)(struct Array*, size_t);

    void (*clear)(struct Array*);
    void (*free)(struct Array*);
} Array;

Array* libexp ArrayNew(void);
void libexp ArrayInit(Array*);
void libexp ArrayFree(Array*);
void libexp ArrayClear(Array*);

boolean libexp ArrayAdd(Array*, void*, size_t, boolean);
boolean libexp ArrayRemove(Array*, size_t);
boolean libexp ArraySwap(Array*, size_t, size_t);
void* libexp ArrayGet(Array*, size_t);

#ifdef	__cplusplus
}
#endif

#endif /* KLIB_ARRAY_H */
