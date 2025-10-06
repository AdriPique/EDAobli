#include "archivo.h"
#include "version.h"
#include "definiciones.h"
#include "funcion_aux.h"
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


// bool existe_version(archivo, char* version)