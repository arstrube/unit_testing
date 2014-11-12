#ifndef __LIST_H_INCLUDED
#define __LIST_H_INCLUDED

//Die Liste wurde als struct implementiert
typedef struct __list_struct __list_t;
//Legt eine neue Liste an
__list_t* __list_create(unsigned int element_size);
//Initialisiert eine Liste und gibt die Elementgroesse an!
int __list_init(__list_t *list, unsigned int element_size);
// Gibt die Anzahl der Element der Liste zurück
int __list_size(__list_t* list);
// Fügt ein Element an einer bestimmten Stelle ein
int __list_insert(__list_t *list,void *element,int index);
// Sucht nach dem erstem, gleichem Element und gibt
// dessen Position zurück
int __list_index(__list_t *list, void *element);
// Kopiert den Wert nach element.
int __list_get(__list_t *list, void* element, int index);
// Wie get, löscht das Element jedoch aus der Liste.
int __list_rem(__list_t *list, void* element, int index);
// Die Liste wird gelöscht.
int __list_destroy(__list_t** list);

#endif // __LIST_H_INCLUDED
