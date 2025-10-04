#include "version.h"
#include "texto.h"

//Estos serían los nodos del arbol, llamados versiones :)
struct nodo_version{
    version ph;
    version sh;
    int nivel;      //Para la referencia cuando tratemos el nombre como un array de enteros,opcional tho.
    int nombre_numerico[100];
    texto* linea;
};




/* proto convertor a numero:
  int nombre_numerico[100];
  char myStr[] = "1.2.3";
  char *myPtr = strtok(myStr, ".");
  while (myPtr != NULL) {
    int i=0;
    nombre_numerico[i]=atoi(*myPtr);
    std::cout << nombre_numerico[i] << endl;
    i++;
    myPtr = strtok(NULL, ".");
  }
  return 0;
}*/