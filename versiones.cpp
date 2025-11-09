#include "versiones.h"
#include "texto.h"
#include "definiciones.h"
#include "archivo.h"
#include "lista_arboles.h"
#include <iostream>
#include "string.h"
using namespace std;


struct nodo_version{
    nodoV ph;
    nodoV sh;
	nodoV padre;
    char* nombre;
    int nivel;      //Para la referencia cuando tratemos el nombre como un array de enteros,opcional tho.
    int numero;
    texto linea;    //Esto es para el texto d euna version
    texto historial;
};


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

nodoV crear_arbol(nodoL l){
   nodoV aux=nuevo_nodo_v();
   setter_arbol_version(l, aux);
   return aux;
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

void def_version_historial(texto nuevo_hist, nodoV v){
    v->historial=nuevo_hist;
}

int numVersion(nodoV v){
    return v->numero;
}

nodoV borrar_arbol(nodoV v){
	if(v==NULL){
        return v;
    } else {
        v->ph=borrar_arbol(v->ph);
        v->sh=borrar_arbol(v->sh);
		eliminar_texto(v->linea);
        eliminar_texto(v->historial);
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

nodoV encontrarVersion (Archivo a, char * version ){
    bool existe = true;
    char * path = strtok(version,".");
    int num = atoi(path);

    nodoL lista = obtener_bosque(a);
    nodoV v;

    // Buscar raíz
    if(lista == NULL){
        return NULL;
    }

    while(lista != NULL && posicion_lista(lista) != num){
        lista = lista_sig(lista);
    }

    if(lista == NULL)
        return NULL;

    v = get_arbol_version(lista);

    // Cada '.' baja un nivel → por cada token bajamos a los hijos
    path = strtok(NULL,".");
    while(existe && path != NULL){
        num = atoi(path);

        // Bajamos un nivel
        v = version_hijo(v);
        if(v == NULL) return NULL;

        // Buscamos entre los hermanos el número correcto
        while(v != NULL && numVersion(v) != num){
            v = version_hermano(v);
        }

        if(v == NULL) return NULL;

        path = strtok(NULL,".");
    }

    return v;
}

nodoV buscarPadre(Archivo a,char * version){
    char * padre= new char [strlen(version)+1]; //+1 por el caracter vacio 
    int pos=0, aca=-1;   
    while(version[pos]!='\0'){
        if(version[pos]=='.'){
            aca=pos;// va a marcar el ultimo elemento donde encuentre el punto
        }
        pos++;       
    }
    if(aca=-1){ //si no tiene punto no tiene padre "estoy en alguna raiz"
        delete [] padre;
        return NULL;
    }

    padre=strcpy(padre,version);
    padre[aca]='\0'; //cortamos en el padre de version para trabajar desde aca

    nodoV papa=encontrarVersion(a,padre);// si no es NULL hay padre , si EXISTE despues podemos ver como trabajar desde aca
    delete [] padre;
    
    return papa;
}

int obtenerUltimoNumero(char *version) {
    char copia[50];
    strcpy(copia, version); // hacemos copia porque strtok modifica el string original

    char *token = strtok(copia, ".");
    int ultimo = atoi(token);

    while (token != NULL) {
        ultimo = atoi(token);
        token = strtok(NULL, ".");
    }

    return ultimo;
}

nodoV buscarHermanoAnterior(Archivo a, char *version) {
    //Buscamos el padre de la versión
    nodoV padre = buscarPadre(a, version);
    if (padre == NULL)
        return NULL; // No hay padre => no puede haber hermanos

    //Obtenemos el número de versión actual
    int numActual = obtenerUltimoNumero(version);

    // Recorremos los hijos del padre para encontrar el hermano anterior
    nodoV hijo = version_hijo(padre);
    nodoV anterior = NULL;

    while (hijo != NULL && numVersion(hijo) < numActual) {
        anterior = hijo;
        hijo = version_hermano(hijo);
    }

    //Si no se encontró hermano anterior, retorna NULL
    return anterior;
}