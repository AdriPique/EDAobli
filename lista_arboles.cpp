#include "lista_arboles.h"
#include "versiones.h"
#include "archivo.h"

struct nodo_lista{
	nodoL siguiente;
	nodoL anterior;
	int posicion;
	nodoV arbolVersion;
};

nodoL lista_sig(nodoL l){
	return l->siguiente;
}

nodoV get_arbol_version(nodoL l){
	return l->arbolVersion;
}


int posicion_lista(nodoL l){
	return l->posicion;
}

void imprimir_arboles(nodoL l){
    while (l!=nullptr){
        imprimir_versiones(l->arbolVersion);
        l=l->siguiente;
    }
}