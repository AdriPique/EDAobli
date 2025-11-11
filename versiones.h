#include "archivo.h"
#include "texto.h"
typedef struct nodo_version* nodoV;
typedef struct nodo_lista* nodoL;

nodoV nuevo_nodo_v();

//Elimina todos los nodos de un arbol y libera toda la memoria.
nodoV borrar_arbol(nodoV v);

bool esRaiz(char *version) ;

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

//Setter del historial de una version, para inicializar.
void def_version_historial(texto nuevo_hist, nodoV v);

int numVersion(nodoV v);

nodoV buscarPadre(Archivo a,char * version);

int obtenerUltimoNumero(char *version);

nodoV buscarHermanoAnterior(Archivo a, char *version);

nodoV encontrarVersion(Archivo a, char* version);

nodoV crear_arbol(nodoL l, char* version, int numero);

void def_version_texto(texto nuevo_texto, nodoV v);
bool insertar_subversion(nodoV padre,  char* version) ;
 nodoV insertar_lista_arboles(nodoV padre, char* version);

void imprimir_versiones_por_nivel(nodoV v, int nivel);
