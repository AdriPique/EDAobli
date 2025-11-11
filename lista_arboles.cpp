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
    int pos = atoi(version);

    nodoL nuevo = new nodo_lista;
    nuevo->anterior = nullptr;
    nuevo->siguiente = nullptr;
    nuevo->posicion = pos;

    nodoL lista = obtener_bosque(a);

    // Lista vacía
    if (lista == NULL){
        if (pos != 1){
            cout << "NO existe la version anterior" << endl;
            delete nuevo;
            return NULL;
        }
        set_bosque(a, nuevo);
        crear_arbol(nuevo, version, pos);
        return nuevo;
    }

    // Inserción al comienzo (pos == 1) con lista NO vacía
    if (pos == 1){
        nuevo->siguiente = lista;
        lista->anterior  = nuevo;
        set_bosque(a, nuevo);
        crear_arbol(nuevo, version, pos);
        return nuevo;
    }

    // Buscar nodo con posicion == pos-1 para insertar después
    nodoL it = lista;
    while (it != NULL && posicion_lista(it) != pos - 1){
        it = lista_sig(it);
    }

    if (it == NULL){
        cout << "NO existe la version anterior" << endl;
        delete nuevo;
        return NULL;
    }

    // Insertar después de 'it'
    nuevo->siguiente = lista_sig(it);
    nuevo->anterior  = it;
    if (lista_sig(it) != NULL) lista_sig(it)->anterior = nuevo;
    it->siguiente = nuevo;

    crear_arbol(nuevo, version, pos);
    return nuevo;
}


void reordenar_lista_raices(Archivo &a)
{
    nodoL lista = obtener_bosque(a);
    if (!lista) return;

    bool cambio;
    do {
        cambio = false;
        nodoL it = lista;

        while (it && lista_sig(it)) {
            nodoL nxt = lista_sig(it);
            if (posicion_lista(it) > posicion_lista(nxt)) {
                // swap de datos en los nodos (sin relinkear punteros)
                int tmpPos = posicion_lista(it);
                Set_posicion_lista(it, posicion_lista(nxt));
                Set_posicion_lista(nxt, tmpPos);

                nodoV tmpV = get_arbol_version(it);
                setter_arbol_version(it, get_arbol_version(nxt));
                setter_arbol_version(nxt, tmpV);

                cambio = true;
            }
            it = lista_sig(it);
        }
    } while (cambio);
}


void Set_posicion_lista (nodoL &l, int x){
	l->posicion=x;
}
