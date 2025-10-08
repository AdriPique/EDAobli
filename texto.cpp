#include "texto.h"
#include <iostream>
using namespace std;
#include <string.h>

//Representa el texto como una lista, nodo=linea.
struct nodo_texto{
    int num_linea;
    char* linea;
    texto sig_linea;
    texto ant_linea;
};

//POS: solo muestra el texto linea por linea, función auxiliar a MostrarTexto.
void recorrer_e_imprimir_texto(texto t, char* nombre_arch, char* version){
    cout << nombre_arch << " - " << version << endl << endl;
    if(t==NULL){
        cout << "No contiene líneas" << endl;
    } else {
        while(t!=NULL){
            cout << t->num_linea << "   " << t->linea << endl;
            t=t->sig_linea;
        }
    }
}

//POS: Retorna el número de lineas de texto de una version.
//PRE: Recibe un puntero al PRIMER elemento de una lista.
int contador_lineas(texto v){
    int cont=1;    
    while(v->sig_linea!=NULL){
        cont++;
        v=v->sig_linea;
    }
    return cont;
}

//POS: Inserta una linea nueva en una posicion estipulada.
void insertar(texto &t, int nmr_linea, char* linea_a_insert){
    
    while(t->num_linea!=nmr_linea){
        t=t->sig_linea;
    }
    if(t==NULL){
        t=new nodo_texto;
        strcpy(t->linea, linea_a_insert);

    } 
}