#include "klib/klib.h"

/**
 * Création et initialisation d'un nouveau pointeur de type List.
 * @return 
 */
List* libexp ListNew(void)
{
    List *this = malloc(sizeof(List));
    ListInit(this);

    return this;
}

/**
 * Initialisation des membres d'un structure List.
 * @param this
 */
void libexp ListInit(List *this)
{
	if(this == NULL)
		return;
	
    this->element = NULL;
    this->size = 0;

    this->add = ListAdd;
    this->remove = ListRemove;
    this->swap = ListSwap;

    this->count = ListCount;
    this->get = ListGet;
    this->getItem = ListGetItem;
    this->getLast = ListGetLast;

    this->clear = ListClear;
    this->free = ListFree;
}

/**
 * Libération de la mémoire allouée pour une List.
 * @param this
 */
void libexp ListFree(List *this)
{
    if(this == NULL)
		return;
	
    this->clear(this);    
    free(this);
}

/**
 * Suppression de l'intégralité des éléments de la List.
 * @param this
 */
void libexp ListClear(List *this)
{
    if(this == NULL)
		return;
	
    while(this->element != NULL)
    {
        ListItem *item = this->element->next;
        free(this->element->value);
        free(this->element);
        this->element = item;
    }
    
    this->size = 0;
}

/**
 * Ajout d'un nouvel élément à une List.
 * Si l'élément est déjà alloué, l'adresse en copiée. Sinon, un nouvel espace est
 * alloué et la valeur est copiée.
 * @param this
 * @param value
 * @param size
 * @param allocated
 * @return
 */
boolean libexp ListAdd(List *this, void *value, size_t size, boolean allocated)
{
    ListItem *last, *item;

    if(this != NULL && value != NULL && (item = malloc(sizeof(ListItem))) != NULL)
    {
        last = this->getLast(this);
        
        if(allocated)
            item->value = value;
        else
        {
            if((item->value = malloc(size)) == NULL)
            {
                free(item);
                return false;
            }
            else
                memcpy(item->value, value, size);
        }
        item->next = NULL;

        if(last == NULL)
            this->element = item;
        else
            last->next = item;
        
        this->size++;
        return true;
    }
    
    return false;
}

/**
 * Suppression de l'élément de List situé à l'indice donné.
 * @param this
 * @param index
 * @return
 */
boolean libexp ListRemove(List *this, size_t index)
{
    if(this == NULL)
		return false;
	
    if(index > 0)
    {
        ListItem *prev = this->getItem(this, index-1);
        ListItem *next = this->getItem(this, index+1);

        free(this->getItem(this, index));
        prev->next = next;
    }
    else if(index == 0 && this->element != NULL)
    {
        ListItem *next = this->element->next;

        free(this->element);
        this->element = next;
    }
    else
        return false;
    
    this->size--;
    return true;
}

/**
 * Inverse deux valeurs d'une List situés aux indices donnés.
 * @param this
 * @param first
 * @param second
 * @return 
 */
boolean libexp ListSwap(List *this, size_t first, size_t second)
{
    if(this == NULL)
		return;
	
    void *value;
    ListItem *firstItem = this->getItem(this, first);
    ListItem *secondItem = this->getItem(this, second);
    
    if(firstItem == NULL || secondItem == NULL)
        return false;
    
    value = firstItem->value;
    firstItem->value = secondItem->value;
    secondItem->value = value;
    return true;
}

/**
 * Renvoie le nombre d'éléments contenus dans la List.
 * @param this
 * @return 
 */
size_t libexp ListCount(List *this)
{
    if(this == NULL)
		return 0;
	
    ListItem *item = this->element;

    for(this->size = 0 ; item != NULL ; this->size++)
        item = item->next;

    return this->size;
}

/**
 * Renvoie le pointeur void correspondant à la valeur de l'élement à l'indice donné.
 * @param this
 * @param index
 * @return 
 */
void* libexp ListGet(List *this, size_t index)
{
    if(this == NULL)
		return NULL;
	
    ListItem *item = this->getItem(this, index);
    return (item != NULL) ? item->value : NULL;
}

/**
 * Renvoie un pointeur sur l'élément de List situé à l'indice donné.
 * @param this
 * @param index
 * @return 
 */
ListItem* libexp ListGetItem(List *this, size_t index)
{
    if(this != NULL && index >= 0 && index < this->size)
	{
		size_t i;
		ListItem *item = this->element;

		for(i = 0 ; i < index ; i++)
		{
			if(item->next != NULL)
				item = item->next;
			else
				break;
		}

		return item;
	}
	
	return NULL;
}

/**
 * Renvoie un pointeur sur le dernier élément alloué de la List.
 * @param this
 * @return 
 */
ListItem* libexp ListGetLast(List *this)
{
    if(this == NULL)
		return;
	
    ListItem *item = this->element;
    
    while(item != NULL)
    {
        if(item->next != NULL)
            item = item->next;
        else
            break;
    }
    
    return item;
}