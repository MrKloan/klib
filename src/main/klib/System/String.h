#ifndef KLIB_STRING_H
#define	KLIB_STRING_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct String {
    char *value;
    size_t length;
    
    boolean (*add)(struct String*, const char);
    boolean (*remove)(struct String*, size_t);
    
    struct String* (*set)(struct String*, const char*);
    char *(*get)(struct String*, size_t);
    struct String* (*in)(struct String*);
    struct String* (*out)(struct String*);
    
    int (*pos)(struct String*, const char);
    int (*exists)(struct String*, struct String*);
    int (*cexists)(struct String*, const char*);
    struct String *(*sub)(struct String*, size_t, size_t);
    struct String* (*copy)(struct String*, struct String*);
    struct String* (*ncopy)(struct String*, struct String*, size_t);
    boolean (*compare)(struct String*, struct String*);
    boolean (*ncompare)(struct String*, struct String*, size_t);
    struct String* (*append)(struct String*, struct String*);
    struct String* (*cappend)(struct String*, const char*);
    struct String* (*trunc)(struct String*, size_t, size_t);
    char *(*toc)(struct String*);
    
    boolean (*startsWith)(struct String*, struct String*);
    boolean (*cstartsWith)(struct String*, const char*);
    boolean (*endsWith)(struct String*, struct String*);
    boolean (*cendsWith)(struct String*, const char*);
    
    struct String* (*clear)(struct String*);
    void (*free)(struct String*);
} String;

String* libexp StringNew(const char*);
String* libexp StringInit(String*, const char*);
void libexp StringFree(String*);

boolean libexp StringAdd(String*, const char);
boolean libexp StringRemove(String*, size_t);
String* libexp StringClear(String*);

String* libexp StringSet(String*, const char*);
char* libexp StringGet(String*, size_t);

String* libexp StringStdin(String*);
String* libexp StringStdout(String*);

int libexp StringPos(String*, const char);
int libexp StringExists(String*, String*);
int libexp StringCExists(String*, const char*);
String* libexp StringSub(String*, size_t, size_t);
String* libexp StringCopy(String*, String*);
String* libexp StringNCopy(String*, String*, size_t);
boolean libexp StringCompare(String*, String*);
boolean libexp StringNCompare(String*, String*, size_t);
String* libexp StringAppend(String*, String*);
String* libexp StringCAppend(String*, const char*);
String* libexp StringTrunc(String*, size_t, size_t);
char* libexp StringToC(String*);

boolean libexp StringStartsWith(String*, String*);
boolean libexp StringCStartsWith(String*, const char*);
boolean libexp StringEndsWith(String*, String*);
boolean libexp StringCEndsWith(String*, const char*);

#ifdef	__cplusplus
}
#endif

#endif	/* KLIB_STRING_H */

