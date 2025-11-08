#include "lista_arboles.h"
#include "versiones.h"
#include "archivo.h"

/*struct nodo_lista{
	nodoL siguiente;
	nodoL anterior;
	int posicion;
	nodoV arbolVersion;
};
*/

nodoL lista_sig(nodoL l){
	return l->siguiente;
}

nodoL lista_ant(nodoL l){
	return l->anterior;
}

void lista_set_sig(nodoL l, nodoL sig){
	l->siguiente=sig;
}
void lista_set_ant(nodoL l, nodoL ant){
	l->anterior=ant;
}


nodoV get_arbol_version(nodoL l){
	return l->arbolVersion;
}


int posicion_lista(nodoL l){
	return l->posicion;
}

void lista_set_posicion(nodoL l, int pos){
	l->posicion=pos;
}

void imprimir_arboles(nodoL l){
    while (l!=nullptr){
        imprimir_versiones(l->arbolVersion);
        l=l->siguiente;
    }
}