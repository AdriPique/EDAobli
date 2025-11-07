#include "archivo.h"
#include "texto.h"
typedef struct nodo_version* nodoV;
nodoV nuevo_nodo_v();
//Elimina todos los nodos de un arbol y libera toda la memoria.
nodoV borrar_arbol(nodoV v);
//Retorna un puntero a la version estipulada o a null si no existe.
nodoV encontrar_version(Archivo a, char* version);


//Retorna el hermano de un nodo.
nodoV version_hermano(nodoV v);

//Retorna el hijo de un nodo.
nodoV version_hijo(nodoV v);

//Retorna el padre de un nodo.
nodoV version_padre(nodoV v);

//Retorna un puntero al texto de un nodo.
texto version_texto(nodoV v);

//Retorna el nombre de un nodo.
char* version_nombre(nodoV v);

//Retorna el puntero al primer nodo de texto de una version.
texto version_linea(nodoV v);

//Retorna un puntero al historial de una version.
texto version_historial(nodoV v);

//Pos: Recorre un arbol finitario e imprime todas los nombres de sus nodos.
//Pre: arbol no vacío, puntero al primer elemento del arbol
void imprimir_versiones(nodoV v);