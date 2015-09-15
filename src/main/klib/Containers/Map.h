#ifndef KLIB_MAP_H
#define	KLIB_MAP_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MAP_NAME_BUFFER 26

typedef struct MapItem {
    char name[MAP_NAME_BUFFER];
    void *value;
    struct MapItem *next;
} MapItem;

typedef struct Map {
    MapItem *element;
    size_t size;

    boolean (*add)(struct Map*, const char*, void*, size_t, boolean);
    boolean (*remove)(struct Map*, const char*);
    boolean (*removeIndex)(struct Map*, size_t);
    
    size_t (*count)(struct Map*);
    int (*index)(struct Map*, const char*);
    
    void *(*get)(struct Map*, const char*);
    void *(*getIndex)(struct Map*, size_t);
    MapItem *(*getItem)(struct Map*, const char*);
    MapItem *(*getItemIndex)(struct Map*, size_t);
    MapItem *(*getLast)(struct Map*);

    void (*clear)(struct Map*);
    void (*free)(struct Map*);
} Map;

Map* libexp MapNew(void);
void libexp MapInit(Map*);
void libexp MapFree(Map*);
void libexp MapClear(Map*);

boolean libexp MapAdd(Map*, const char*, void*, size_t, boolean);
boolean libexp MapRemove(Map*, const char*);
boolean libexp MapRemoveIndex(Map*, size_t);

size_t libexp MapCount(Map*);
int libexp MapIndex(Map*, const char*);
void* libexp MapGet(Map*, const char*);
void* libexp MapGetIndex(Map*, size_t);
MapItem* libexp MapGetItem(Map*, const char*);
MapItem* libexp MapGetItemIndex(Map*, size_t);
MapItem* libexp MapGetLast(Map*);

#ifdef	__cplusplus
}
#endif

#endif	/* KLIB_MAP_H */

