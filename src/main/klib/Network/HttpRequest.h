#ifndef KLIB_HTTPREQUEST_H
#define	KLIB_HTTPREQUEST_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum {
    HTTP = 80,
    HTTPS = 443
} REQUEST_PROTOCOL;

typedef struct HttpRequest {
    Socket *socket;
    char *hostname;
    REQUEST_PROTOCOL protocol;
    
    struct HttpRequest *(*get)(struct HttpRequest*, const char*, const char*);
    
    void (*free)(struct HttpRequest*);
} HttpRequest;

HttpRequest* libexp HttpRequestNew(char*, REQUEST_PROTOCOL);
HttpRequest* libexp HttpRequestInit(HttpRequest*, char*, REQUEST_PROTOCOL);

HttpRequest* libexp HttpRequestGet(HttpRequest*, const char*, const char*);

void libexp HttpRequestFree(HttpRequest*);

#ifdef	__cplusplus
}
#endif

#endif	/* KLIB_HTTPREQUEST_H */

