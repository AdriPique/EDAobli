#include "versiones.h"
#include "texto.h"
#include "definiciones.h"
#include "archivo.h"
#include "lista_arboles.h"
#include <iostream>
#include "string.h"
using namespace std;

nodoV nuevo_nodo_v(){
    nodoV v = new nodo_version;
    v->historial=NULL;
    v->linea=NULL;
    v->nivel= 0;
    v->nombre=NULL;
    v->numero= 0;
    v->padre=NULL;
    v->ph=NULL;
    v->sh=NULL;
    return v;
}

//Post: devuelve el hermano de una version.
nodoV version_hermano(nodoV v){
    return v->sh;
}

//Post: devuelve el hijo de una version.
nodoV version_hijo(nodoV v){
    return v->ph;
}

//Post: devuelve el padre de una version.
nodoV version_padre(nodoV v){
    return v->padre;
}

//Post: devuelve el texto de una version.
texto version_texto(nodoV v){
    return v->linea;
}

char* version_nombre(nodoV v){
    return v->nombre;
}

texto version_linea(nodoV v){
    return v->linea;
}

texto version_historial(nodoV v){
    return v->historial;
}

nodoV borrar_arbol(nodoV v){
	if(v==NULL){
        return v;
    } else {
        v->ph=borrar_arbol(v->ph);
        v->sh=borrar_arbol(v->sh);
		eliminar_texto(v->linea);
        delete v;
        v=NULL;
        return v;
    }
}

nodoV encontrar_version(Archivo a, char* version){
    //Pre: Saber que la version que queremos trabajar no es la primera 
    //Post: Si existe version te devuelve la version en la que queremos trabajar
    //Si no existe te devuelve null 
    cout << version << endl << endl << endl;
	nodoL pos_lista= obtener_bosque(a);
	if(pos_lista==NULL){
		return NULL;
	} else {
    while(pos_lista!=NULL && posicion_lista(pos_lista)!=((int)*version-48)){
		pos_lista=lista_sig(pos_lista);
	}
	if(pos_lista==NULL){
		return NULL;
	} else {
	nodoV quiero=get_arbol_version(pos_lista);
	int i=0;
	int xd;
    bool existe= false;
    char actuall[MAX_NOMBRE];
	actuall[0]='\0';
	char* actual=actuall;
	while(existe == false && version[i]!= '\0'){
	
        if(quiero->numero==(int)version[i]-48){//si el numero es igual nos metemos en ese puntero || probando con codigo ASCII 
            cout << "entre al if uwu " << endl;
			actuall[i]=quiero->numero+48;
			actuall[i+1]='\0';
            i=i+2; // nos paramos en el siguiente valor del string de aux
            if(strcmp(version, actual)==0){//si actual y version son iguales existe version y cortamo
                cout << "a ver si son iguales " << endl;
				existe= true;
            }
			actual[i+1]='.';
        } else if((quiero->sh!=NULL)&&( quiero->sh->numero==version[i]-48)){ //si la version en la que estamos parados tiene un hermano y esta version hermana nos sirve nos movemos
            cout << "entre al else if 1 " << endl;
			quiero=quiero->sh;// solo me muevo en sub versiones (hacia la derecha) si el siguiente numero me sirve

        } else if((quiero->ph!=NULL)&& (quiero->ph->numero>=version[i]-48)){//siempre que el hijo sea mayor o igual sigo bajando
            cout << "entre al else if 2 " << endl;
			quiero=quiero->ph;
        }
        else {
			cout << "entre al else normal " << endl;
            i=i+2;//si no existe la version pero sigue habiendo que recorrer el string version lo recorremos 
        }

    }      
    if(existe)
        return quiero;
    else
        return NULL;
	} 
	}    
}

//Pos: Recorre un arbol finitario e imprime todas los nombres de sus nodos.
//Pre: arbol no vacío, puntero al primer elemento del arbol
void imprimir_versiones(nodoV v){
    if(v==NULL){
        
    } else {
        cout << v->nombre << endl;              //Ver como implementar lo de los espacios por nivel.
        if(v->sh!=NULL){
            imprimir_versiones(v->sh);
        } else if(v->ph!=NULL){
            imprimir_versiones(v->ph);
        }
    }
}
