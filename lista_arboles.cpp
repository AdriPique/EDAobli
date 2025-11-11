#include "lista_arboles.h"
#include "versiones.h"
#include "archivo.h"
#include "string.h"
#include <iostream>
using namespace std;

struct nodo_lista{
	nodoL siguiente;
	nodoL anterior;
	int posicion;
	nodoV raiz_arbol;
};

nodoL lista_sig(nodoL l){
	return l->siguiente;
}

nodoL lista_ant(nodoL l){
	return l->anterior;
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
    nodoL aux = obtener_bosque(a);
    while (aux != nullptr){
        if (x == aux->posicion) return true;
        aux = aux->siguiente;                      
    }
    return false;
}


nodoL crear_nodo_l(Archivo &a, char* version){
	int pos= atoi(version);
	nodoL aux;
	nodoL lista = obtener_bosque(a);
	aux=new nodo_lista;
	aux->anterior=nullptr;
	aux->siguiente=nullptr;
	aux->posicion=pos;
	if(lista==NULL){
		set_bosque(a,aux);
		nodoV aux2=crear_arbol(aux, version, pos);
		return aux;
	} else {
		while(lista!=NULL){
			if(lista->posicion==pos-1){
				lista->siguiente=aux;
				aux->anterior=lista;
				nodoV aux2=crear_arbol(aux, version, pos);
				return aux;
			} else {
				lista=lista->siguiente;
			}
		}
		cout << "NO existe la version anterior" << endl;
		delete aux;
		return NULL;
	}
}





void Set_posicion_lista (nodoL &l, int x){
	l->posicion=x;
}
