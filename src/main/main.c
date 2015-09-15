#include "klib/klib.h"

/*/ARRAY
typedef struct Point {
    int x, y;
} Point;

int main(int argc, char** argv)
{
    Array *arr = ArrayNew();
    Point *a = malloc(sizeof(Point)), *b = malloc(sizeof(Point));
    float f = 42.f;
    size_t i;
    
    a->x = b->y = -5;
    a->y = b->x = 50;
    
    arr->add(arr, a, sizeof(a), true);
    arr->add(arr, &f, sizeof(f), false);
    arr->add(arr, b, sizeof(b), true);
    
    printf("Float : %.2f\n", *(float*)arr->get(arr, 1));
    
    a = (Point*)arr->get(arr, 0);
    b = (Point*)arr->get(arr, 2);
    printf("A=[%d:%d], B=[%d:%d]\n", a->x, a->y, b->x, b->y);
    
    arr->swap(arr, 0, 2);
    a = (Point*)arr->get(arr, 0);
    b = (Point*)arr->get(arr, 2);
    printf("A=[%d:%d], B=[%d:%d]\n", a->x, a->y, b->x, b->y);
    
    arr->swap(arr, 0, 1);
    printf("Float : %.2f\n", *(float*)arr->get(arr, 0));
    
    arr->clear(arr);
    printf("Size : %u\n", (unsigned int)arr->size);
    
    f = 9;
    arr->add(arr, &f, sizeof(f), 0);
    f = 3;
    arr->add(arr, &f, sizeof(f), 0);
    f = 5;
    arr->add(arr, &f, sizeof(f), 0);
    f = 10;
    arr->add(arr, &f, sizeof(f), 0);
    
    for(i=0 ; i < arr->size ; i++)
        printf("Value %u : %.0f\n", (unsigned short)i+1, *(float*)arr->get(arr, i));
    
    puts("REMOVING");
    arr->remove(arr, 2);
    arr->remove(arr, 0);
    
    for(i=0 ; i < arr->size ; i++)
        printf("Value %u : %.0f\n", (unsigned short)i+1, *(float*)arr->get(arr, i));
    
    puts("SWAPPIN'");
    
    arr->swap(arr, 0, 1);
    
    for(i=0 ; i < arr->size ; i++)
        printf("Value %u : %.0f\n", (unsigned short)i+1, *(float*)arr->get(arr, i));

    arr->free(arr);
    return 0;
}//*/

/*/LIST
typedef struct Point {
    int x, y;
} Point;

int main(int argc, char **argv)
{
    List *list = ListNew();
    Point *a = malloc(sizeof(Point)), *b = malloc(sizeof(Point));
    float f = 42.f;
    size_t i;
    
    a->x = b->y = -5;
    a->y = b->x = 50;
    
    list->add(list, a, sizeof(a), 1);
    list->add(list, &f, sizeof(f), 0);
    list->add(list, b, sizeof(b), 1);
    
    printf("Float : %.2f\n", *(float*)list->get(list, 1));
    
    a = (Point*)list->get(list, 0);
    b = (Point*)list->get(list, 2);
    printf("A=[%d:%d], B=[%d:%d]\n", a->x, a->y, b->x, b->y);
    
    list->swap(list, 0, 2);
    a = (Point*)list->get(list, 0);
    b = (Point*)list->get(list, 2);
    printf("A=[%d:%d], B=[%d:%d]\n", a->x, a->y, b->x, b->y);
    
    list->swap(list, 0, 1);
    printf("Float : %.2f\n", *(float*)list->get(list, 0));
    
    list->clear(list);
    printf("Size : %u\n", (unsigned int)list->size);
    
    f = 9;
    list->add(list, &f, sizeof(f), 0);
    f = 3;
    list->add(list, &f, sizeof(f), 0);
    f = 5;
    list->add(list, &f, sizeof(f), 0);
    f = 10;
    list->add(list, &f, sizeof(f), 0);
    
    for(i=0 ; i < list->size ; i++)
        printf("Value %u : %.0f\n", (unsigned short)i+1, *(float*)list->get(list, i));
    
    list->clear(list);
    
    char *test = "Coucou";
    list->add(list, test, strlen(test)+1, 0);
    printf("%s\n", (char*)list->get(list, 0));

    list->free(list);
    return 0;
}//*/

//MAP
int main(int argc, char** argv)
{
    Map *map = MapNew();
    int i = 42;
    char *hello = "Hello World!";
    
    map->add(map, "value1", &i, sizeof(i), 0);
    i++;
    map->add(map, "value2", &i, sizeof(i), 0);
    i++;
    map->add(map, "value3", &i, sizeof(i), 0);
    map->add(map, "hello", hello, strlen(hello)-3, 0);
    map->add(map, "test", "Coucou", 7, 0);
    
    printf("%s\n", (char*)map->get(map, "hello"));
    printf("%d\n", *(int*)map->get(map, "value1"));
    printf("%d\n", *(int*)map->get(map, "value3"));
    printf("%d\n", *(int*)map->get(map, "value2"));
    printf("%s\n", (char*)map->get(map, "test"));
    
    map->free(map);
    return EXIT_SUCCESS;
}//*/

/*/Queue
int main(int argc, char** argv)
{
    Queue *list = QueueNew();
    int i, count;
    
    for(i=0 ; i < 10 ; i++)
    {
        list->push(list, &i, sizeof(i), 0);
        printf("Push : %d\n", i);
    }
    
    count = list->count(list);
    printf("Count : %d\n", count);
    for(i=0 ; i < count ; i++)
    {
        int *p = (int*)list->pop(list);
        printf("Pop : %d\n", *p);
        free(p);
    }
    
    list->free(list);
    return EXIT_SUCCESS;
}//*/

/*/STACK
int main(int argc, char** argv)
{
    Stack *stack = StackNew();
    int i, count;
    
    for(i=0 ; i < 10 ; i++)
    {
        stack->push(stack, &i, sizeof(i), 0);
        printf("Push : %d\n", i);
    }
    
    count = stack->count(stack);
    printf("Count : %d\n", count);
    for(i=0 ; i < count ; i++)
    {
        int *p = stack->pop(stack);
        printf("Pop : %d\n", *p);
        free(p);
    }
    
    stack->free(stack);
    return (EXIT_SUCCESS);
}//*/

/*/STRING
int main(int argc, char **argv)
{
    String *hw = StringNew("Hello World!");
    String *h = StringNew("Hello");
    String *w = StringNew("World!");
    
    if(hw->endsWith(hw, w))
        puts("OK");
    else
        puts("Nope.");
    
    hw->free(hw);
    h->free(h);
    w->free(w);
    
    return 0;
}*/