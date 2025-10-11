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
//PRE: Recibe un puntero al PRIMER elemento de una lista o uno nulo en caso de lista vacía.
int contador_lineas(texto v){
    if(v==NULL){
        return 0;
    } else {
    int cont=1;    
    while(v->sig_linea!=NULL){
        cont++;
        v=v->sig_linea;
    }
    return cont;
    }
}

//POS: Inserta una linea nueva en una posicion estipulada.
void insertar(texto &t, int nmr_linea, char* linea_a_insert){
     texto auxT=new nodo_texto;
     auxT->linea=linea_a_insert;
     auxT->num_linea=nmr_linea;
     auxT->ant_linea=NULL;
     auxT->sig_linea=NULL;

    if (t==NULL){
        t=auxT;

    } else if(nmr_linea==1){
        auxT->sig_linea=t;
        auxT->ant_linea=NULL;
        t->ant_linea=auxT;
        t=auxT;
        auxT= auxT->sig_linea;
        while(auxT!=NULL){
            auxT->num_linea++;
            auxT=auxT->sig_linea;
        } 
    } else {
        texto movil=t;
        while(movil->num_linea!=nmr_linea && movil->sig_linea!=NULL){
            movil=movil->sig_linea;
        }    
        if(movil->num_linea==nmr_linea){
            movil->ant_linea->sig_linea=auxT;
            auxT->ant_linea=movil->ant_linea;
            auxT->sig_linea=movil;
            movil->ant_linea=auxT;
            while(movil!=NULL){
                movil->num_linea++;
                movil=movil->sig_linea;
            }                
        } else {
            movil->sig_linea=auxT;
            auxT->ant_linea=movil;
        }
    }
    
}

void borrar(texto &t, int nmr_linea){
    texto aux=t;
    if(nmr_linea==1){
        t=t->sig_linea;
        t->ant_linea=NULL;
        delete aux;
        aux=t;
    } else {
        while(nmr_linea!=aux->num_linea){
            aux=aux->sig_linea;
        }
        texto aux2=aux;
        aux->ant_linea->sig_linea=aux->sig_linea;
        aux->sig_linea->ant_linea=aux->ant_linea;
        aux=aux->sig_linea;
        delete aux2;
    }
     while(aux!=NULL){
            aux->num_linea--;
            aux=aux->sig_linea;
        }
}