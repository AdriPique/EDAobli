#include "archivo.h"
#include "version.h"
#include "definiciones.h"
#include <iostream>
using namespace std;


void imprimir_versiones(Archivo a){
    if(a->versiones==NULL){
        cout << a->nombre << endl;
        cout << "No hay versiones vreadas" << endl;
    } else{
        version aux= a->versiones;
        cout << endl;
        for(int i=aux->nivel; i>0; i--){
            cout << "   ";
        }
        cout << aux-> nombre_en_int[i];
        
    }
}


// bool existe_version(archivo, char* version)