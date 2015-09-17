#include "klib/klib.h"

Stack* libexp StackNew(void)
{
    Stack *this = malloc(sizeof(Stack));
    StackInit(this);
    
    return this;
}

void libexp StackInit(Stack *this)
{
	if(this != NULL)
	{
		this->element = NULL;
		this->size = 0;

		this->push = StackPush;
		this->pop = StackPop;
		this->count = StackCount;
		this->clear = StackClear;
		this->free = StackFree;
	}
}

void libexp StackFree(Stack *this)
{
	if(this != NULL)
	{
		this->clear(this);
		free(this);
	}
}

boolean libexp StackPush(Stack *this, void *value, size_t size, boolean allocated)
{
	if(this != NULL && value != NULL)
	{
		StackItem *item = malloc(sizeof(StackItem));

		if(allocated)
			item->value = value;
		else
		{
			item->value = malloc(size);
			memcpy(item->value, value, size);
		}
		item->size = size;
		item->next = this->element;
		this->element = item;

		this->size++;
		return true;
	}
	
	return false;
}

void* libexp StackPop(Stack *this)
{
	if(this != NULL)
	{
		StackItem *next = this->element->next;
		void *value = malloc(this->element->size);
		memcpy(value, this->element->value, this->element->size);

		free(this->element);
		this->element = next;

		this->size--;
		return value;
	}
	
	return NULL;
}

size_t libexp StackCount(Stack *this)
{
	if(this != NULL)
	{
		StackItem *temp = this->element;

		for(this->size = 0 ; temp != NULL ; this->size++)
			temp = temp->next;

		return this->size;
	}
	
	return 0;
}

void libexp StackClear(Stack *this)
{
	if(this != NULL)
	{
		while(this->element != NULL)
		{
			StackItem *item = this->element->next;
			free(this->element->value);
			free(this->element);
			this->element = item;
		}

		this->size = 0;
	}
}
