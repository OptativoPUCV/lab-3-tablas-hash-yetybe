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



/*No inserte claves repetidas. 
Recuerde que el arreglo es **circular**.
Recuerde actualizar la variable size.
*/

long resolveCollision(HashMap * map , long posicion , char* clave)
{
    while(map->current < map->capacity)
    {
        if (map->current != NULL || is_equal(map->buckets[posicion]->key , clave))
        {
            posicion++;
            map->current ++;
        }
        else
        {
            return posicion;
        }
        
    }
    return -1;

}


   
void insertMap(HashMap * map, char * key, void * value)
{
    long posicion = hash(key , map->capacity);
    if (map->buckets[posicion] == NULL || map->buckets[posicion]->key == -1) 
    {
        Pair *nuevoElemento = createPair(key , value);
        map->buckets[posicion] = nuevoElemento;
    }
    else
    {
        long  newPosition = resolveCollision(map, posicion , key);
        Pair * nuevoElemento = createPair(key , value);
        map->buckets[newPosition] = nuevoElemento;

    }



void enlarge(HashMap * map) {
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

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
