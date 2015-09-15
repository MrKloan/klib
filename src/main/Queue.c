#include "klib/klib.h"

Queue* libexp QueueNew(void)
{
    Queue *this = malloc(sizeof(Queue));
    QueueInit(this);
    
    return this;
}

void libexp QueueInit(Queue *this)
{
	if(this == NULL)
		return;
	
    this->element = NULL;
    this->size = 0;
    
    this->push = QueuePush;
    this->pop = QueuePop;
    this->count = QueueCount;
    this->clear = QueueClear;
    this->free = QueueFree;
}

void libexp QueueFree(Queue *this)
{
	if(this == NULL)
		return;
	
    this->clear(this);
    free(this);
}

void libexp QueuePush(Queue *this, void *value, size_t size, boolean allocated)
{
	if(this == NULL || value == NULL)
		return;
	
    QueueItem *last = this->element, *item = malloc(sizeof(QueueItem));
    
    while(last != NULL)
    {
        if(last->next != NULL)
            last = last->next;
        else
            break;
    }

    if(allocated)
        item->value = value;
    else
    {
        item->value = malloc(size);
        memcpy(item->value, value, size);
    }
    item->size = size;
    item->next = NULL;

    if(last == NULL)
        this->element = item;
    else
        last->next = item;
    
    this->size++;
}

void* libexp QueuePop(Queue *this)
{
	if(this == NULL)
		return;
	
    void *value = NULL;
    
    if(this->element != NULL)
    {
        QueueItem *next = this->element->next;
        value = malloc(this->element->size);
        memcpy(value, this->element->value, this->element->size);

        free(this->element);
        this->element = next;
    }
    
    this->size--;
    return value;
}

size_t libexp QueueCount(Queue *this)
{
	if(this == NULL)
		return 0;
	
    QueueItem *item = this->element;

    for(this->size = 0 ; item != NULL ; this->size++)
        item = item->next;

    return this->size;
}

void libexp QueueClear(Queue *this)
{
	if(this == NULL)
		return;
	
    while(this->element != NULL)
    {
        QueueItem *item = this->element->next;
        free(this->element->value);
        free(this->element);
        this->element = item;
    }
    
    this->size = 0;
}
