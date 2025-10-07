#include "archivo.h"
#include "definiciones.h"
#include<string.h>
#include <iostream>

using namespace std;


void imprimir_versiones(Archivo a){
    if(a->versiones==NULL){
        cout << a->nombre << endl;
        cout << "No hay versiones creadas" << endl;
    } else{
        Archivo aux= a->versiones;
        cout << endl;
        for(int i=aux->nivel; i>0; i--){
            cout << "   ";
        }
        cout << aux-> nombre_en_int[i];
        
    }
}

void liberarTexto(texto t){
    while(t != NULL){
        texto temp = t;
        t = t -> sig_linea;
        delete [] temp->linea;
        delete temp;
    }

}
void liberarVersiones(version v){
    if (v == NULL) return;
        liberarVersiones(v->ph);
        liberarVersiones(v->sh);
        if (v->linea != NULL)
        liberarTexto(*(v->linea));
        delete v;
}


Archivo existe_version(Archivo a, char* version){
    if(a->ph==NULL){
        if(a->sh==NULL){
            if(strcmp(version,a->nombre)==0)
                return a;
            else 
                return NULL;
        }
        
    }else{
            existe_version(a->ph, version);
        }



}
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
bool compararToken(Archivo a,char * version){
    bool igual= false;
    char* myVer = strtok(aux->nombre,".");
    char* Ver = strtok(version, "."); 
    while (version!=NULL&& aux->nombre!= NULL){
        if(strcmp(myVer,Ver)==0){
            igual=true;
            char* myVer = strtok(aux->nombre,".");
            char* Ver = strtok(version, ".");

        }else{
            igual=false;
        }
    }
    return igual;
}
// Mal pero la idea está.
Archivo encontrar_nodo(Archivo a, char* version){
    //Recorre estructura y te para donde esta la version si existe
   
    Archivo aux =a;
    while()
    if((compararToken( aux,version)==false )&&(aux->ph!=NULL)){
        aux= aux->ph;

    }else if(compararToken())
    




    

    if (a == NULL) 
        return NULL;
    bool encontrado=false;
    if(a->ph!=NULL && !encontrado){
        encontrar_nodo(a->ph, version);
    } else if(a->sh!=NULL && !encontrado){
        encontrar_nodo(a->sh, version);
    } else{
        if(strcmp(a->nombre, version)==0){
            encontrado=true;
        }
    }
    return a;
    
}