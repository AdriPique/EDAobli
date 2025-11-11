#include "texto.h"
#include "versiones.h"
#include <iostream>
using namespace std;
#include <string.h>

//Representa el texto como una lista, nodo=linea.
struct nodo_texto{
    int num_linea;
    char* linea;
    texto sig_linea;
    texto ant_linea;
    string insert_o_borr;
};

texto nuevo_nodo_texto(){
    texto tex= new nodo_texto;
    tex->num_linea=0;
    tex->linea=NULL;
    tex->sig_linea=NULL;
    tex->ant_linea=NULL;
    return tex;
}

//POS: solo muestra el texto linea por linea, función auxiliar a MostrarTexto.
void recorrer_e_imprimir_texto(texto t, char* nombre_arch, char* version){
    cout << nombre_arch << " - " << version << endl << endl;
    if(t==NULL){
        cout << "No contiene lineas" << endl;
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
    int cont=0;    
    while(v!=NULL){
        cont++;
        v=v->sig_linea;
    }
    return cont;
}

//POS: Inserta una linea nueva en una posicion estipulada.
void insertar(texto &t, int nmr_linea, char* linea_a_insert, nodoV v){
     texto auxT=new nodo_texto;
     auxT->linea=strdup (linea_a_insert);
     auxT->num_linea=nmr_linea;
     auxT->ant_linea=NULL;
     auxT->sig_linea=NULL;
     insertar_cambio_historial(v, nmr_linea, linea_a_insert, 0);


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
        while( movil->sig_linea!=NULL && movil->num_linea!=nmr_linea){
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

//POS: Inserta una linea en la ultima posicion del historial de una version con el cambio realizado, ya sea eliminar o insertar linea.
texto insertar_cambio_historial(nodoV v, int nmr_linea, char* linea_a_insert, int x){
    texto auxH=new nodo_texto;
    auxH->linea=strdup (linea_a_insert);
    auxH->num_linea=nmr_linea;
    auxH->ant_linea=NULL;
    auxH->sig_linea=NULL;
    texto aux= version_historial(v);
    if (x==0){
        auxH->insert_o_borr= strdup("IL");
    } else {
        auxH->insert_o_borr= strdup("BL");
    }
    if (aux==NULL){
        def_version_historial(auxH, v);
    } else{
        while(aux->sig_linea!=NULL){
            aux=aux->sig_linea;
        }
        aux->sig_linea=auxH;
        auxH->ant_linea=aux;
    }
    return NULL;
}

void imprimir_historial(nodoV v){
    texto aux= version_historial(v);
    while(aux!=NULL){
        cout << aux->insert_o_borr << "    " << aux->num_linea << "    " << aux->linea << endl;
        aux= aux->sig_linea;
    }
}

//POS: Elimina una línea específica del texto, corrigiendo la posicion del resto.

void eliminar_linea(texto &t, int nmr_linea, nodoV v) {
    if (t == NULL) return;


    texto aux = t;
    while (aux != NULL && aux->num_linea != nmr_linea) {
        aux = aux->sig_linea;
    }
    if (aux == NULL) return; // no existe

    // Guardar en historial la línea real antes de borrarla
    if (aux->linea != NULL)
        insertar_cambio_historial(v, nmr_linea, aux->linea, 1);

    // Si solo hay una línea
    if (aux->ant_linea == NULL && aux->sig_linea == NULL) {
        free(aux->linea);
        delete aux;
        t = NULL;
        return;
    }

    if (aux->ant_linea == NULL) {
        t = aux->sig_linea;
        t->ant_linea = NULL;
        def_version_texto(t, v);
    }
 
    else if (aux->sig_linea == NULL) {
        aux->ant_linea->sig_linea = NULL;
    }
   
    else {
        aux->ant_linea->sig_linea = aux->sig_linea;
        aux->sig_linea->ant_linea = aux->ant_linea;
    }

   
    free(aux->linea);
    delete aux;

    
    texto recorrer = t;
    int i = 1;
    while (recorrer != NULL) {
        recorrer->num_linea = i++;
        recorrer = recorrer->sig_linea;
    }
}





//POS:Elimina todo el texto de una version.
//PRE: Puntero al primer elemento de la lista de texto.
void eliminar_texto(texto &t){
    texto aux=t;
    while(t!=NULL){
        t=t->sig_linea;
        delete aux;
        aux=t;
    }
    t=NULL;
}

texto siguientelinea(texto t){
    return t->sig_linea;
}
int  numerolinea(texto t){
    return t-> num_linea;
}
void linea(texto t,char * &s){ 
    s=strdup(t->linea);
    
}

bool textos_iguales(texto t1, texto t2){
    texto aux1 = t1;
    texto aux2 = t2;

    while(aux1 != NULL && aux2 != NULL){
        if(aux1->num_linea != aux2->num_linea){
            return false;
        }
        if(aux1->linea == NULL || aux2->linea == NULL){
            if(aux1->linea != aux2->linea){
                return false;
            }
        } else if(strcmp(aux1->linea, aux2->linea) != 0){
            return false;
        }

        aux1 = aux1->sig_linea;
        aux2 = aux2->sig_linea;
    }

    return aux1 == NULL && aux2 == NULL;
}