#ifndef KLIB_BOOLEAN_H
#define	KLIB_BOOLEAN_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef unsigned char boolean;

#define false 0
#define true !false

typedef enum {
	False = false,
	True = true
} Boolean;

#ifdef	__cplusplus
}
#endif

#endif	/* KLIB_BOOLEAN_H */

