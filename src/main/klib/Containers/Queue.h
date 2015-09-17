#ifndef KLIB_QUEUE_H
#define	KLIB_QUEUE_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct QueueItem {
    void *value;
    size_t size;
    struct QueueItem *next;
} QueueItem;

typedef struct Queue {
    QueueItem *element;
    size_t size;
    
    boolean (*push)(struct Queue*, void*, size_t, boolean);
    void *(*pop)(struct Queue*);
    size_t (*count)(struct Queue*);
    void (*clear)(struct Queue*);
    void (*free)(struct Queue*);
} Queue;

Queue* libexp QueueNew(void);
void libexp QueueInit(Queue*);
void libexp QueueFree(Queue*);

boolean libexp QueuePush(Queue*, void*, size_t, boolean);
void* libexp QueuePop(Queue*);
size_t libexp QueueCount(Queue*);
void libexp QueueClear(Queue*);
    
#ifdef	__cplusplus
}
#endif

#endif	/* KLIB_QUEUE_H */

