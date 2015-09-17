#ifndef KLIB_TREE_H
#define	KLIB_TREE_H

#include "Array.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct Branch {
	void *leave;
	
	Array *nodes;
	size_t size;
} Branch;

typedef struct Tree {
	Branch *trunk;
} Tree;

void libexp TreeNew(void);
void libexp TreeInit(Tree*);
void libexp TreeFree(Tree*);
void libexp TreeClear(Tree*);

Branch* libexp TreeGetNode(Branch*, size_t);

#ifdef	__cplusplus
}
#endif

#endif	/* KLIB_TREE_H */

