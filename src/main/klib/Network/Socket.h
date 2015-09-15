#ifndef KLIB_SOCKET_H
#define	KLIB_SOCKET_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#ifdef WIN32
    #include <windows.h>
    #include <winsock2.h>

    typedef size_t socklen_t;

#elif defined (linux)
    #define libexp
    #define libexp

    #include <errno.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <netdb.h>

    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close(s)

    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
    typedef struct in_addr IN_ADDR;
    typedef struct hostent HOSTENT;
    typedef struct timeval timeval;
#else
    #error "No kLib support has been developed for your platform so far."
#endif

#define SOCKET_BUFFER 1024

typedef enum {
    SOCKET_TCP,
    SOCKET_UDP
} SOCKET_TYPE;

typedef struct Socket
{
    SOCKET_TYPE type;
    SOCKET socket;
    SOCKADDR_IN infos;
    unsigned short waitQueue;
    
    String *buffer;
    unsigned short bufferSize;
    
    unsigned char (*setHost)(struct Socket*, const char*, unsigned short);
    unsigned char (*connect)(struct Socket*, const char*, unsigned short);
    unsigned char (*reuse)(struct Socket*);
    unsigned char (*bind)(struct Socket*, unsigned short);
    
    struct Socket *(*listen)(struct Socket*);
    unsigned char (*send)(struct Socket*);
    unsigned char (*sendTo)(struct Socket*, SOCKADDR_IN*);
    String *(*receive)(struct Socket*);
    String *(*receiveFrom)(struct Socket*);
    
    int (*error)(void);
    char *(*strerror)(void);
    struct Socket *(*close)(struct Socket*);
    void (*free)(struct Socket*);
} Socket;

unsigned char libexp SocketStart(void);
unsigned char libexp SocketEnd(void);
int libexp SocketError(void);
char* libexp SocketStrError(void);

Socket* libexp SocketNew(SOCKET_TYPE);
Socket* libexp SocketInit(Socket*, SOCKET_TYPE);
Socket* libexp SocketClose(Socket*);
void libexp SocketFree(Socket*);

unsigned char libexp SocketSetHost(Socket*, const char*, unsigned short);
unsigned char libexp SocketConnect(Socket*, const char*, unsigned short);
unsigned char libexp SocketReuse(Socket*);
unsigned char libexp SocketBind(Socket*, unsigned short);

Socket* libexp SocketListen(Socket*);
unsigned char libexp SocketSend(Socket*);
unsigned char libexp SocketSendTo(Socket*, SOCKADDR_IN*);
String* libexp SocketReceive(Socket*);
String* libexp SocketReceiveFrom(Socket*);

#ifdef	__cplusplus
}
#endif

#endif	/* KLIB_SOCKET_H */

