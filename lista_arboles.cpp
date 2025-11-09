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

void setter_arbol_version(nodoL &l, nodoV v){
	l->raiz_arbol=v;
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

bool existe_numero(Archivo a, int x){
	nodoL aux=obtener_bosque(a);
	bool existe=false;
	while(aux!=NULL){
		if(x==aux->posicion){
			existe=true;
		}
	}
	return existe;
}