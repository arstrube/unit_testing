#include "__list.h"

#include <stdlib.h>
#include <string.h>

typedef struct __item_struct __item_t;

// Details of __list_struct and __item_struct now private
struct __item_struct
{
    void* data;
    __item_t *next;
};

struct __list_struct
{
    int size;
    int elem_size;
    __item_t header;
};
//

//Erzeugt eine neue Liste und gibt deren Adresse zur�ck
__list_t* __list_create(unsigned int element_size)
{
    __list_t *list = malloc(sizeof(__list_t));
    list->elem_size = element_size;
    list->size = 0;
    list->header.next = NULL;

    return list;
}

// Gibt die Anzahl der Element der Liste zur�ck
int __list_size(__list_t *list)
{
    return list->size;
}

// F�gt ein Element an einer bestimmten Stelle ein
int __list_insert(__list_t *list,void *element,int index)
{
    int i;
    __item_t *new_item;
    __item_t *current_item = &list->header;

    if (index > list->size || index < 0) return -1;
    for (i = 0; i < index; i++)
    {
        current_item = current_item->next;
    }
    new_item = malloc(sizeof(__item_t));
    new_item->next = current_item->next;
    new_item->data = malloc(list->elem_size);
    current_item->next = new_item;
    memcpy(new_item->data, element, list->elem_size);
    list->size++;
    return EXIT_SUCCESS;
}
// Sucht nach dem erstem, gleichem Element und gibt
// dessen Position zur�ck
int __list_index(__list_t *list, void *element)
{

    int i;
    __item_t *current_item = list->header.next;

    for (i = 0; current_item != NULL; i++)
    {

        if(0 == memcmp(element,current_item->data,list->size)) return i;
        current_item = current_item->next;
    }

    return -1;
}
// Kopiert den Wert nach element.
int __list_get(__list_t *list, void* element, int index)
{
    int i;
    __item_t *current_item = list->header.next;
    if (index > list->size || index < 0) return -1;
    for (i=0; i < index; i++)
    {
        current_item = current_item->next;
    }

    memcpy(element,current_item->data,list->elem_size);


    return EXIT_SUCCESS;
}
// Wie get, l�scht das Element jedoch aus der Liste.
int __list_rem(__list_t *list, void* element, int index)
{
    int i;
    __item_t *current_item = &list->header;
    __item_t *deadman;
    if (index > list->size || index < 0) return -1;
    for (i=0; i < index; i++)
    {
        current_item = current_item->next;
    }

    memcpy(element,current_item->next->data,list->elem_size);
    deadman = current_item->next;
    current_item->next = deadman->next;
    free(deadman->data);
    free(deadman);
    list->size--;

    return EXIT_SUCCESS;
}
// l�scht die gesamte Liste und gibt den Speicher frei
int __list_destroy(__list_t **list)
{
    __item_t* current = (*list)->header.next;
    while(current != 0) {
        __item_t* next = current->next;
        current->data = 0;
        current->next = 0;
        free(current);
        current = next;
    }
    free(*list);
    *list = 0;

    return EXIT_SUCCESS;
}
