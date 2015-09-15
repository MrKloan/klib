#include "klib/klib.h"

/**
 * Création et initialisation d'un nouveau pointeur de type Array.
 * @return 
 */
Array* libexp ArrayNew(void)
{
    Array *this = malloc(sizeof(Array));
    ArrayInit(this);

    return this;
}

/**
 * Initialisation des membres d'un structure Array.
 * @param this
 */
void libexp ArrayInit(Array *this)
{
    if(this == NULL)
		return;
	
    this->element = NULL;
    this->size = 0;

    this->add = ArrayAdd;
    this->remove = ArrayRemove;
    this->swap = ArraySwap;
    this->get = ArrayGet;

    this->clear = ArrayClear;
    this->free = ArrayFree;
}

/**
 * Libération de la mémoire allouée pour une Array.
 * @param this
 */
void libexp ArrayFree(Array *this)
{
    if(this == NULL)
		return;
	
    this->clear(this);    
    free(this);
}

/**
 * Suppression de l'intégralité des éléments de la Array.
 * @param this
 */
void libexp ArrayClear(Array *this)
{
    if(this == NULL)
		return;
	
    size_t i;
    
    for(i = 0 ; i < this->size ; i++)
        free(this->element[i]);
    free(this->element);
    this->element = NULL;
    
    this->size = 0;
}

/**
 * Ajout d'un nouvel élément à une Array.
 * Si l'élément est déjà alloué, l'adresse en copiée. Sinon, un nouvel espace est
 * alloué et la valeur est copiée.
 * @param this
 * @param value
 * @param size
 * @param allocated
 * @return
 */
boolean libexp ArrayAdd(Array *this, void *value, size_t size, boolean allocated)
{
    if(this != NULL && value != NULL && (this->element = realloc(this->element, ++this->size * sizeof(void*))) != NULL)
    {
        if(allocated)
            this->element[this->size-1] = value;
        else
        {
            if((this->element[this->size-1] = malloc(size)) == NULL)
            {
                this->element = realloc(this->element, --this->size * sizeof(void*));
                return 0;
            }
            else
                memcpy(this->element[this->size-1], value, size);
        }

        return true;
    }
    
    return false;
}

/**
 * Suppression de l'élément de Array situé à l'indice donné.
 * @param this
 * @param index
 * @return
 */
boolean libexp ArrayRemove(Array *this, size_t index)
{
    void **tmp = NULL;
    
    if(this != NULL && index >= 0 && index < this->size
    && (tmp = malloc(--this->size * sizeof(void*))) != NULL)
    {
        size_t i;
        unsigned char flag = 0;

        for(i = 0 ; i < this->size+1 ; i++)
        {
            if(i == index)
            {
                //On ne libère que l'élément qu'on souhaite supprimer
                free(this->element[i]);
                
                flag = 1;
                continue;
            }

            //Les autres éléments sont sauvegardés
            tmp[i - flag] = this->element[i];
        }
        free(this->element);

        this->element = tmp;
        return true;
    }

    return false;
}

/**
 * Inverse deux valeurs d'une Array situés aux indices donnés.
 * @param this
 * @param first
 * @param second
 * @return 
 */
boolean libexp ArraySwap(Array *this, size_t first, size_t second)
{
    if(this != NULL 
	&& first >= 0 && first < this->size
    && second >= 0 && second < this->size)
    {
        void *tmp = this->element[first];
        this->element[first] = this->element[second];
        this->element[second] = tmp;
        
        return true;
    }
    
    return false;
}

/**
 * Renvoie le pointeur void correspondant à la valeur de l'élement à l'indice donné.
 * @param this
 * @param index
 * @return 
 */
void* libexp ArrayGet(Array *this, size_t index)
{
    return (this != NULL && index >= 0 && index < this->size) ? this->element[index] : NULL;
}