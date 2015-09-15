#include "klib/klib.h"

String* libexp StringNew(const char *value)
{
    String *this = NULL;
    
    if((this = malloc(sizeof(String))) != NULL)
        StringInit(this, value);

    return this;
}

String* libexp StringInit(String *this, const char *value)
{
    if(this != NULL)
    {
        this->value = NULL;
        this->length = 0;

        this->add = StringAdd;
        this->remove = StringRemove;

        this->set = StringSet;
        this->get = StringGet;
        this->in = StringStdin;
        this->out = StringStdout;

        this->pos = StringPos;
        this->exists = StringExists;
        this->cexists = StringCExists;
        this->sub = StringSub;
        this->copy = StringCopy;
        this->ncopy = StringNCopy;
        this->compare = StringCompare;
        this->ncompare = StringNCompare;
        this->append = StringAppend;
        this->cappend = StringCAppend;
        this->trunc = StringTrunc;
        this->toc = StringToC;

        this->startsWith = StringStartsWith;
        this->cstartsWith = StringCStartsWith;
        this->endsWith = StringEndsWith;
        this->cendsWith = StringCEndsWith;

        this->clear = StringClear;
        this->free = StringFree;

        if(value != NULL)
            this->set(this, value);
    }
    
    return this;
}

void libexp StringFree(String *this)
{
    if(this != NULL)
    {
        this->clear(this);
        free(this);
    }
}

boolean libexp StringAdd(String *this, const char c)
{
    if(this != NULL && (this->value = realloc(this->value, ++this->length * sizeof(char))) != NULL)
    {
        this->value[this->length-1] = c;
        return true;
    }
    
    return false;
}

boolean libexp StringRemove(String *this, size_t index)
{
    size_t i;
    boolean found = false;
    char *temp = NULL;

    if(this != NULL && index >= 0 && index < this->length)
    {
        if((temp = (char*)malloc(--this->length * sizeof(char))) != NULL)
        {
            for(i = 0 ; i < this->length ; i++)
            {
                if(i == index)
                    found = true;
                
                temp[i] = this->value[found ? i+1 : i];
            }

            free(this->value);
            this->value = temp;
            
            return true;
        }
    }
    
    return false;
}

String* libexp StringClear(String *this)
{
    if(this != NULL && this->length > 0 && this->value != NULL)
    {
        free(this->value);
        this->value = NULL;
        this->length = 0;
    }
    
    return this;
}

String* libexp StringSet(String *this, const char *value)
{
    if(this != NULL)
    {
        size_t i;

        this->clear(this);

        if(value != NULL)
        {
            for(i = 0 ; value[i] != '\0' ; i++)
                this->add(this, value[i]);
        }
    }
    
    return this;
}

char* libexp StringGet(String *this, size_t index)
{
    if(this != NULL && index >= 0 && index < this->length)
        return &this->value[index];
    else
        return NULL;
}

String* libexp StringStdin(String *this)
{
    if(this != NULL)
    {
        char c;

        this->clear(this);

        while((c = getchar()) != '\n')
            this->add(this, c);
    }
    
    return this;
}

String* libexp StringStdout(String *this)
{
    if(this != NULL && this->length > 0 && this->value != NULL)
    {
        size_t i;
        
        for(i = 0 ; i < this->length ; i++)
            printf("%c", this->value[i]);
        printf("\n");
    }
    
    return this;
}

int libexp StringPos(String *this, const char search)
{
    if(this != NULL)
    {
        size_t i;

        for(i = 0 ; i < this->length ; i++)
        {
            if(this->value[i] == search)
                return i;
        }
    }
        
    return -1;
}

int libexp StringExists(String *this, String *search)
{
    if(this != NULL && search != NULL && this->length > search->length)
    {
        size_t i, j, k = this->length - search->length;

        for(i = 0 ; i < k ; i++)
        {
            boolean found = true;

            for(j = 0 ; j < search->length ; j++)
            {
                if(this->value[i+j] != search->value[j])
                {
                    found = false;
                    break;
                }
            }

            if(found)
                return i;
        }
    }
    
    return -1;
}

int libexp StringCExists(String *this, const char *search)
{
    if(this != NULL && search != NULL)
    {
        size_t search_length = 0;

        while(search[search_length] != '\0')
            search_length++;
        
        if(this->length > search_length)
        {
            size_t i, j, k = this->length - search_length;

            for(i = 0 ; i < k ; i++)
            {
                boolean found = true;

                for(j = 0 ; j < search_length ; j++)
                {
                    if(this->value[i+j] != search[j])
                    {
                        found = false;
                        break;
                    }
                }

                if(found)
                    return i;
            }
        }
    }
    
    return -1;
}

String* libexp StringSub(String *this, size_t start, size_t end)
{
    if(this != NULL && this->length > 0 && start >= 0 && end < this->length && start <= end)
    {
        size_t i;
        String *str = StringNew(NULL);
    
        for(i = start ; i <= end ; i++)
            str->add(str, this->value[i]);
        
        return str;
    }
    
    return NULL;
}

String* libexp StringCopy(String *this, String *src)
{
    if(this != NULL && src != NULL)
        this->set(this, src->value);
    
    return this;
}

String* libexp StringNCopy(String *this, String *src, size_t size)
{
    if(this != NULL && src != NULL && size >= 0 && size < src->length)
    {
        size_t i;

        this->clear(this);

        for(i = 0 ; i < size ; i++)
            this->add(this, src->value[i]);
    }
    
    return this;
}

boolean libexp StringCompare(String *this, String *str)
{
    if(this != NULL && str != NULL && this->length == str->length)
    {
        size_t i;
        boolean found = false;
        
        for(i = 0 ; i < this->length ; i++)
        {
            if(this->value[i] != str->value[i])
            {
                found = true;
                break;
            }
        }
        
        return !found;
    }
    
    return false;
}

boolean libexp StringNCompare(String *this, String *str, size_t size)
{
    if(this != NULL && str != NULL && size > 0 && this->length >= size && str->length >= size)
    {
        size_t i;
        boolean found = false;
        
        for(i = 0 ; i < size ; i++)
        {
            if(this->value[i] != str->value[i])
            {
                found = true;
                break;
            }
        }
        
        return !found;
    }
    
    return false;
}

String* libexp StringAppend(String *this, String *str)
{
    size_t i;
    
    if(this != NULL && str != NULL)
    {
        for(i = 0 ; i < str->length ; i++)
            this->add(this, str->value[i]);
    }
    
    return this;
}

String* libexp StringCAppend(String *this, const char *str)
{
    size_t i;
    
    if(this != NULL && str != NULL)
    {
        for(i = 0 ; str[i] != '\0' ; i++)
            this->add(this, str[i]);
    }
        
    return this;
}

String* libexp StringTrunc(String *this, size_t start, size_t end)
{
    if(this != NULL && start >= 0 && end < this->length && start < end)
    {
        size_t i, j = end - start;
        char temp[j];

        for(i = 0 ; i < j ; i++)
            temp[i] = this->value[i+start];
        temp[i] = '\0';

        this->set(this, temp);
    }
    
    return this;
}

char* libexp StringToC(String *this)
{
    if(this != NULL)
    {
        char *str = NULL;
        
        if((str = malloc(this->length*sizeof(char))) != NULL)
        {
            size_t i;
            
            for(i = 0 ; i < this->length ; i++)
                str[i] = this->value[i];
            str[i] = '\0';

            return str;
        }
    }
    
    return NULL;
}

boolean libexp StringStartsWith(String *this, String *str)
{
    return (this != NULL && str != NULL) ? this->ncompare(this, str, str->length) : false;
}

boolean libexp StringCStartsWith(String *this, const char *str)
{
    if(this != NULL && str != NULL)
    {
        String *tmp = StringNew(str);
        boolean flag = this->startsWith(this, tmp);

        tmp->free(tmp);
        return flag;
    }
    
    return false;
}

boolean libexp StringEndsWith(String *this, String *str)
{
    if(this != NULL && str != NULL)
    {
        String *sub = this->sub(this, this->length - str->length, this->length - 1);
        boolean flag = sub->compare(sub, str);

        sub->free(sub);
        return flag;
    }
    
    return false;
}

boolean libexp StringCEndsWith(String *this, const char *str)
{
    if(this != NULL && str != NULL)
    {
        String *tmp = StringNew(str);
        boolean flag = this->endsWith(this, tmp);

        tmp->free(tmp);
        return flag;
    }
    
    return false;
}