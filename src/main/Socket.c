#include "klib/klib.h"

unsigned char libexp SocketStart(void)
{
#ifdef WIN32
    WSADATA wsa;
    if(WSAStartup(MAKEWORD(2,2), &wsa) == 0)
        return 1;
    else
        return 0;
#elif defined (linux)
    return 1;
#endif
}

unsigned char libexp SocketEnd(void)
{
#ifdef WIN32
    if(WSACleanup() == 0)
        return 1;
    else
        return 0;
#elif defined (linux)
    return 1;
#endif
}

int libexp SocketError(void)
{
#ifdef WIN32
    return WSAGetLastError();
#elif defined (linux)
    return errno;
#endif
}

char* libexp SocketStrError(void)
{
#ifdef WIN32
    LPTSTR buff;

    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
                  NULL,
                  WSAGetLastError(),
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                  (LPTSTR)&buff,
                  SOCKET_BUFFER,
                  NULL
    );
    return buff;

#elif defined (linux)
    return strerror(errno);
#endif
}

Socket* libexp SocketNew(SOCKET_TYPE type)
{
    Socket *this = NULL;
    
    if((type == SOCKET_TCP || type == SOCKET_UDP)
    && (this = malloc(sizeof(Socket))) != NULL)
        SocketInit(this, type);
    
    return this;
}

Socket* libexp SocketInit(Socket *this, SOCKET_TYPE type)
{
    this->type = type;
    this->socket = INVALID_SOCKET;
    this->waitQueue = 5;
    
    this->buffer = StringNew(NULL);
    this->bufferSize = 1024;
    
    this->setHost = SocketSetHost;
    this->connect = SocketConnect;
    this->reuse = SocketReuse;
    this->bind = SocketBind;
    
    this->listen = SocketListen;
    this->send = SocketSend;
    this->sendTo = SocketSendTo;
    this->receive = SocketReceive;
    this->receiveFrom = SocketReceiveFrom;
    
    this->error = SocketError;
    this->strerror = SocketStrError;
    this->close = SocketClose;
    this->free = SocketFree;
    
    if((this->socket = socket(AF_INET, (this->type == SOCKET_TCP) ? SOCK_STREAM : SOCK_DGRAM, 0)) == INVALID_SOCKET)
        return this;
    else
        return NULL;
}

Socket* libexp SocketClose(Socket *this)
{
    if(this->socket != INVALID_SOCKET)
        closesocket(this->socket);
}

void libexp SocketFree(Socket *this)
{
    this->close(this);
    this->buffer->free(this->buffer);
}

unsigned char libexp SocketSetHost(Socket *this, const char *hostname, unsigned short port)
{
    HOSTENT *hostinfo = gethostbyname(hostname);

    if(hostinfo == NULL)
        return 0;
    else
    {
        this->infos.sin_addr = *((IN_ADDR*)hostinfo->h_addr);
        this->infos.sin_port = htons(port);
        this->infos.sin_family = AF_INET;
        
        return 1;
    }
    
    return 0;
}

unsigned char libexp SocketConnect(Socket *this, const char *hostname, unsigned short port)
{
    if(this->setHost(this, hostname, port)
    && connect(this->socket, (SOCKADDR*)&this->infos, sizeof(this->infos)) != SOCKET_ERROR)
        return 1;
    else
        return 0;
}

unsigned char libexp SocketReuse(Socket *this)
{
    if(setsockopt(this->socket, SOL_SOCKET, SO_REUSEADDR, "1", sizeof(char)) == SOCKET_ERROR)
        return 0;
    else
        return 1;
}

unsigned char libexp SocketBind(Socket *this, unsigned short port)
{
    this->infos.sin_addr.s_addr = htonl(INADDR_ANY);
    this->infos.sin_family = AF_INET;
    this->infos.sin_port = htons(port);

    if(this->reuse(this) && bind(this->socket, (SOCKADDR*)&this->infos, sizeof(this->infos)) != SOCKET_ERROR)
        return 1;
    else
        return 0;
}

Socket* libexp SocketListen(Socket *this)
{
    if(listen(this->socket, this->waitQueue) == SOCKET_ERROR)
        return NULL;
    else
    {
        int info_size;
        Socket *client = SocketNew(SOCKET_TCP);

        info_size = sizeof(client->infos);

        if((client->socket = accept(this->socket, (SOCKADDR*)&client->infos, (socklen_t*)&info_size)) != INVALID_SOCKET)
            return client;
        else
        {
            client->free(client);
            return NULL;
        }
    }
}

unsigned char libexp SocketSend(Socket *this)
{
    if(send(this->socket, this->buffer->toc(this->buffer), this->buffer->length, 0) < 0)
        return 0;
    else
        return 1;
}

unsigned char libexp SocketSendTo(Socket *this, SOCKADDR_IN *to)
{
    if(sendto(this->socket, this->buffer->toc(this->buffer), this->buffer->length, 0, (SOCKADDR*)to, (socklen_t)sizeof(to)) < 0)
        return 0;
    else
        return 1;
}

String* libexp SocketReceive(Socket *this)
{
    int n;
    char buffer[this->bufferSize];

    this->buffer->clear(this->buffer);
    
    while((n = recv(this->socket, buffer, this->bufferSize-1, 0)) > -1)
    {
        buffer[n] = '\0';
        this->buffer->cappend(this->buffer, buffer);
    }
    
    return this->buffer;
}

String* libexp SocketReceiveFrom(Socket *this)
{
    int n, info_size;
    char buffer[this->bufferSize];

    this->buffer->clear(this->buffer);
    
    while((n = recvfrom(this->socket, buffer, this->bufferSize-1, 0, (SOCKADDR*)&this->infos, (socklen_t*)&info_size)) > -1)
    {
        buffer[n] = '\0';
        this->buffer->cappend(this->buffer, buffer);
    }
    
    return this->buffer;
}