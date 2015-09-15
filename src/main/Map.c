#include "klib/klib.h"

/**
 * Création et initialisation d'un nouveau pointeur de type Map.
 * @return 
 */
Map* libexp MapNew(void)
{
    Map *this = malloc(sizeof(Map));
    MapInit(this);

    return this;
}

/**
 * Initialisation des membres d'une structure Map.
 * @param this
 */
void libexp MapInit(Map *this)
{
	if(this == NULL)
		return;
	
    this->element = NULL;
    this->size = 0;

    this->add = MapAdd;
    this->remove = MapRemove;
    this->removeIndex = MapRemoveIndex;

    this->count = MapCount;
    this->index = MapIndex;

    this->get = MapGet;
    this->getIndex = MapGetIndex;
    this->getItem = MapGetItem;
    this->getItemIndex = MapGetItemIndex;
    this->getLast = MapGetLast;

    this->clear = MapClear;
    this->free = MapFree;
}

/**
 * Libération de la mémoire allouée pour une Map.
 * @param this
 */
void libexp MapFree(Map *this)
{
	if(this == NULL)
		return;
	
    this->clear(this);
    free(this);
}

/**
 * Suppression de l'intégralité des éléments de la Map.
 * @param this
 */
void libexp MapClear(Map *this)
{
    if(this == NULL)
		return;
	
    while(this->element != NULL)
    {
        MapItem *item = this->element->next;
        free(this->element->value);
        free(this->element);
        this->element = item;
    }
    
    this->size = 0;
}

/**
 * Ajout d'un nouvel élément à une Map.
 * Si l'élément est déjà alloué, l'adresse en copiée. Sinon, un nouvel espace est
 * alloué et la valeur est copiée.
 * @param this
 * @param name
 * @param value
 * @param size
 * @param allocated
 * @return
 */
boolean libexp MapAdd(Map *this, const char *name, void *value, size_t size, boolean allocated)
{
    MapItem *last, *item;

    if(this == NULL || value == NULL || strlen(name) >= MAP_NAME_BUFFER)
        return false;

    if((item = malloc(sizeof (MapItem))) != NULL)
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
        strcpy(item->name, name);
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
 * Suppression de l'élément de Map possédant le nom donné.
 * @param this
 * @param name
 * @return
 */
boolean libexp MapRemove(Map *this, const char *name)
{
    int index;

    if(this != NULL && name != NULL && (index = this->index(this, name)) != 0)
        return this->removeIndex(this, index);

    return false;
}

/**
 * Suppression de l'élément de Map situé à l'indice donné.
 * @param this
 * @param index
 * @return
 */
boolean libexp MapRemoveIndex(Map *this, size_t index)
{
    if(this == NULL)
		return false;
	
	if(index > 0)
    {
        MapItem *prev = this->getItemIndex(this, index - 1);
        MapItem *next = this->getItemIndex(this, index + 1);

        free(this->getItemIndex(this, index));
        prev->next = next;
    }
    else if(index == 0 && this->element != NULL)
    {
        MapItem *next = this->element->next;

        free(this->element);
        this->element = next;
    }
    else
        return false;

    this->size--;
    return true;
}

/**
 * Renvoie le nombre d'éléments contenus dans la Map.
 * @param this
 * @return 
 */
size_t libexp MapCount(Map *this)
{
    if(this == NULL)
		return 0;
	
	MapItem *item = this->element;

    for(this->size = 0 ; item != NULL ; this->size++)
        item = item->next;

    return this->size;
}

/**
 * Renvoie l'indice d'un élément de Map possédant le nom donné.
 * @param this
 * @param name
 * @return 
 */
int libexp MapIndex(Map *this, const char *name)
{
    if(this != NULL && name != NULL)
	{	
		int i;
		MapItem *item = this->element;

		for(i = 0 ; item != NULL ; i++)
		{
			if(!strcmp(item->name, name))
				return i;

			item = item->next;
		}
	}
	
    return -1;
}

/**
 * Renvoie le pointeur void correspondant à la valeur de l'élement possédant le
 * nom donné.
 * @param this
 * @param name
 * @return 
 */
void* libexp MapGet(Map *this, const char *name)
{
    return (this != NULL && name != NULL) ? this->getItem(this, name)->value : NULL;
}

/**
 * Renvoie le pointeur void correspondant à la valeur de l'élement à l'indice donné.
 * @param this
 * @param index
 * @return 
 */
void* libexp MapGetIndex(Map *this, size_t index)
{
    return (this != NULL) ? this->getItemIndex(this, index)->value : NULL;
}

/**
 * Renvoie un pointeur sur l'élément de Map possédant le nom donné.
 * @param this
 * @param name
 * @return 
 */
MapItem* libexp MapGetItem(Map *this, const char *name)
{
	if(this != NULL && name != NULL)
	{
		MapItem *item = this->element;

		while(item != NULL)
		{
			if(!strcmp(item->name, name))
				return item;

			item = item->next;
		}
	}
	
    return NULL;
}

/**
 * Renvoie un pointeur sur l'élément de Map situé à l'indice donné.
 * @param this
 * @param index
 * @return 
 */
MapItem* libexp MapGetItemIndex(Map *this, size_t index)
{
	if(this != NULL && index >= 0 && index < this->size)
	{
		size_t i;
		MapItem *item = this->element;

		for(i = 0 ; i < index ; i++)
			item = item->next;

		return item;
	}
	
	return NULL;
}

/**
 * Renvoie un pointeur sur le dernier élément alloué de la Map.
 * @param this
 * @return 
 */
MapItem* libexp MapGetLast(Map *this)
{
	if(this == NULL)
		return NULL;
	
    MapItem *item = this->element;

    while (item != NULL)
    {
        if(item->next != NULL)
            item = item->next;
        else
            break;
    }

    return item;
}
