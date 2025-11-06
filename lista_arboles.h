typedef struct nodo_lista* nodoL;
#include "versiones.h"


//Devuleve el siguiente elemento de una lista
nodoL lista_sig(nodoL l);

//Devuelve el arbol de un nodo de la lista de versiones
nodoV get_arbol_version(nodoL l);

//Devuelve la posicion de la lista de un nodo.
int posicion_lista(nodoL l);

//Recorre la lista bosque e imprime los arboles
void imprimir_arboles(nodoL l);