#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap *map, char *key, void *value) 
{
    if (map == NULL || key == NULL) return;

    long posicion = hash(key, map->capacity);
    long original_pos = posicion;

    do {
        
        if (map->buckets[posicion] == NULL || 
            (map->buckets[posicion] != NULL && map->buckets[posicion]->key == NULL)) {
            
            Pair *nuevoElemento = createPair(strdup(key), value);
            map->buckets[posicion] = nuevoElemento;
            map->current = posicion;
            map->size++;
            return;
        }
        
        
        if (is_equal(map->buckets[posicion]->key, key)) {
            return; 
        }

        
        posicion = (posicion + 1) % map->capacity;

    } while (posicion != original_pos);

    
    enlarge(map);
    insertMap(map, key, value); 
}


void enlarge(HashMap * map) 
{
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) 
{
    HashMap *mapa = (HashMap*)malloc(sizeof(HashMap));
    if (mapa == NULL)return NULL;
       
    mapa->buckets = (Pair **) calloc (capacity,sizeof(Pair *));
    if (mapa->buckets == NULL)return NULL;

    mapa->current = -1;
    mapa->size = 0;
    mapa->capacity = capacity;
    return mapa; 
    
}

/*
4.- Implemente la función void eraseMap(HashMap * map,  char * key). Está función elimina el dato correspondiente a la clave key. Para hacerlo debe buscar el dato y luego *marcarlo* para que no sea válido.
**No elimine el par**, sólo invalídelo asignando NULL a la clave (pair->key=NULL).
Recuerde actualizar la variable size.
*/


void eraseMap(HashMap * map,  char * key) 
{
    long pos = hash(key , map->capacity);
    Pair *hasElement = map->buckets[pos];
    if (hasElement != NULL && hasElement->key != NULL && is_equal(hasElement->key  , key)) 
    {
        map->buckets[pos]->value = NULL;
        map->size --;
        return;
    }    
    else
    {
        while(map->buckets[pos] != NULL)
        {
            pos = (pos + 1) % map->capacity;
            Pair *temp = map->buckets[pos];
            if (temp != NULL && temp->key != NULL && is_equal(temp->key  , key)) 
            {
                map->buckets[pos]->value = NULL;
                map->size--;
                return;

            }
        }
    }

    return;
}    
    
Pair * searchMap(HashMap * map,  char * key) 
{ 
    long pos = hash(key , map->capacity);
    Pair *hasElement = map->buckets[pos];
    if (hasElement != NULL && hasElement->key != NULL && is_equal(hasElement->key  , key)) 
    {
        map->current = pos;
        return hasElement;
    }    
    else
    {
        while(map->buckets[pos] != NULL)
        {
            pos = (pos + 1) % map->capacity;
            Pair *temp = map->buckets[pos];
            if (temp != NULL && temp->key != NULL && is_equal(temp->key  , key)) 
            {
                map->current = pos;
                return temp;

            }
        }
    }

    return NULL;
}
    

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}

  
