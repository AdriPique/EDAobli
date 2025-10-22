#include "archivo.h"
#include "texto.h"
typedef struct nodo_version* nodoV;
nodoV nuevo_nodo_v();
nodoV borrar_arbol(nodoV v);
nodoV encontrar_version(Archivo a, char* version);
nodoL get_bosque(Archivo a);
nodoV version_hermano(nodoV v);
nodoV version_hijo(nodoV v);
nodoV version_padre(nodoV v);
texto version_texto(nodoV v);
char* version_nombre(nodoV v);
