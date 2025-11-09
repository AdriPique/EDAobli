#include "lista_arboles.h"
#include "versiones.h"
#include "archivo.h"

struct nodo_lista{
	nodoL siguiente;
	nodoL anterior;
	int posicion;
	nodoV raiz_arbol;
};

nodoL lista_sig(nodoL l){
	return l->siguiente;
}

nodoV get_arbol_version(nodoL l){
	return l->raiz_arbol;
}


int posicion_lista(nodoL l){
	return l->posicion;
}

void imprimir_arboles(nodoL l){
    while (l!=nullptr){
        imprimir_versiones(l->raiz_arbol);
        l=l->siguiente;
    }
}