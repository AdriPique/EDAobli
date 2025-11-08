#ifndef LISTA_ARBOLES_H
#define LISTA_ARBOLES_H

#ifndef TIPO_NODOL_DEF
#define TIPO_NODOL_DEF
struct nodo_lista;
typedef struct nodo_lista* nodoL;
#endif

#include "versiones.h"

struct nodo_lista{
    nodoL siguiente;
    nodoL anterior;
    int posicion;
    nodoV arbolVersion;
};


//Devuleve el siguiente elemento de una lista
nodoL lista_sig(nodoL l);

//Devuelve el elemento anterior de una lista
nodoL lista_ant(nodoL l);

//Establece el siguiente elemento de la lista
void lista_set_sig(nodoL l, nodoL sig);

//Establece el elemento anterior de la lista
void lista_set_ant(nodoL l, nodoL ant);


//Devuelve el arbol de un nodo de la lista de versiones
nodoV get_arbol_version(nodoL l);

//Devuelve la posicion de la lista de un nodo.
int posicion_lista(nodoL l);

//Establece la posicion de un nodo en la lista
void lista_set_posicion(nodoL l, int pos);

//Recorre la lista bosque e imprime los arboles
void imprimir_arboles(nodoL l);

#endif
