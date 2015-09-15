#include "klib/klib.h"

HttpRequest* libexp HttpRequestNew(char *hostname, REQUEST_PROTOCOL protocol)
{
    HttpRequest *this = NULL;
    
    if(hostname != NULL
    && (protocol == HTTP || protocol == HTTPS)
    && (this = malloc(sizeof(HttpRequest))) != NULL)
        HttpRequestInit(this, hostname, protocol);
    
    return this;
}

HttpRequest* libexp HttpRequestInit(HttpRequest *this, char *hostname, REQUEST_PROTOCOL protocol)
{
    this->socket = SocketNew(SOCKET_TCP);
    this->hostname = hostname;
    this->protocol = protocol;
    
    this->get = HttpRequestGet;
    
    this->free = HttpRequestFree;
    
    return this;
}

HttpRequest* libexp HttpRequestGet(HttpRequest *this, const char *path, const char *params)
{
    char buffer[1024];
    
    this->socket->connect(this->socket, this->hostname, this->protocol);
    
    sprintf(buffer, "GET %s%s HTTP/1.1\r\nHost: %s\r\n\r\n", path, params, this->hostname);
    this->socket->buffer->set(this->socket->buffer, buffer);
    
    if(this->socket->send(this->socket))
        puts("SENT");
                
    this->socket->receive(this->socket);
    
    this->socket->close(this->socket);
    
    return this;
}

void HttpRequestFree(HttpRequest *this)
{
    this->socket->free(this->socket);
    free(this);
}