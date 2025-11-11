#include "versiones.h"
typedef struct nodo_lista* nodoL;


//Devuleve el siguiente elemento de una lista
nodoL lista_sig(nodoL l);

//Devuelve el arbol de un nodo de la lista de versiones
nodoV get_arbol_version(nodoL l);

//Devuelve la posicion de la lista de un nodo.
int posicion_lista(nodoL l);

//Recorre la lista bosque e imprime los arboles
void imprimir_arboles(nodoL l);

void setter_arbol_version(nodoL &l, nodoV v);

bool existe_numero(Archivo a, int x);

nodoL crear_nodo_l(Archivo &a, char* version);
void Set_posicion_lista (nodoL &l, int x);

nodoL lista_ant(nodoL l);