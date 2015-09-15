#ifndef KLIB_STACK_H
#define	KLIB_STACK_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct StackItem {
    void *value;
    size_t size;
    struct StackItem *next;
} StackItem;

typedef struct Stack {
    StackItem *element;
    size_t size;
    
    void (*push)(struct Stack*, void*, size_t, boolean);
    void *(*pop)(struct Stack*);
    size_t (*count)(struct Stack*);
    void (*clear)(struct Stack*);
    void (*free)(struct Stack*);
} Stack;

Stack* libexp StackNew(void);
void libexp StackInit(Stack*);
void libexp StackFree(Stack*);

void libexp StackPush(Stack*, void*, size_t, boolean);
void* libexp StackPop(Stack*);
size_t libexp StackCount(Stack*);
void libexp StackClear(Stack*);
    
#ifdef	__cplusplus
}
#endif

#endif	/* KLIB_STACK_H */

