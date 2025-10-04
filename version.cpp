#include "version.h"

//Estos serían los nodos del arbol, llamados versiones :)
struct nodo_version{
    version ph;
    version sh;
    int nivel;      //Para la referencia cuando tratemos el nombre como un array de enteros,opcional tho.

};

