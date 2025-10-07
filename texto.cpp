#include "texto.h"


//Representa el texto como una lista, nodo=linea.
struct nodo_texto{
    int num_linea;
    char* linea;
    texto sig_linea;
    texto ant_linea;
};
