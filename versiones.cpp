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

nodoV crear_arbol(nodoL l, char* version, int numero){
   nodoV aux = nuevo_nodo_v();
   aux->nivel = 1;
   aux->nombre = strdup(version);   
   aux->numero = numero;
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
        texto aux=v->linea;
        eliminar_texto(aux);
        eliminar_texto(v->historial);
        delete v;
        v=NULL;
        return v;
    }
}


void imprimir_versiones(nodoV v){
    if(v==NULL){
        
    } else {
        cout << v->nombre << endl;            
        if(v->sh!=NULL){
            imprimir_versiones(v->sh);
        } else if(v->ph!=NULL){
            imprimir_versiones(v->ph);
        }
    }
}

bool esRaiz(char *version) {
    // Si la version no contiene un punto es raiz
    return (strchr(version, '.') == NULL);
}
nodoV encontrarVersion (Archivo a, char *version ){

    if (a == NULL || version == NULL) return NULL;

   
    char copia[64];
    strncpy(copia, version, sizeof(copia));
    copia[sizeof(copia)-1] = '\0';

  
    char* tok = strtok(copia, ".");
    if (tok == NULL) return NULL;

    int num = atoi(tok);

    nodoL lista = obtener_bosque(a);
    while (lista != NULL && posicion_lista(lista) != num)
        lista = lista_sig(lista);

    if (lista == NULL) return NULL;

    nodoV v = get_arbol_version(lista);

   
    tok = strtok(NULL, ".");
    while (tok != NULL){

        num = atoi(tok);

   
        v = version_hijo(v);
        if (v == NULL) return NULL;

      
        while (v != NULL && numVersion(v) != num)
            v = version_hermano(v);

        if (v == NULL) return NULL;

        tok = strtok(NULL, ".");
    }

    return v;
}

nodoV buscarPadre(Archivo a,char * version){
    char * padre= new char [strlen(version)+1];
    int pos=0, aca=-1;   
    while(version[pos]!='\0'){
        if(version[pos]=='.'){
            aca=pos;
        }
        pos++;       
    }
    if(aca==-1){ 
        delete [] padre;
        return NULL;
    }

    padre=strcpy(padre,version);
    padre[aca]='\0'; 

    nodoV papa=encontrarVersion(a,padre);
    delete [] padre;
    
    return papa;
}

int obtenerUltimoNumero(char *version) {
    char copia[50];
    strcpy(copia, version); 

    char *token = strtok(copia, ".");
    int ultimo = atoi(token);

    while (token != NULL) {
        ultimo = atoi(token);
        token = strtok(NULL, ".");
    }

    return ultimo;
}

nodoV buscarHermanoAnterior(Archivo a, char *version) {

    nodoV padre = buscarPadre(a, version);
    if (padre == NULL)
    return NULL; 

 
    int numActual = obtenerUltimoNumero(version);

  
    nodoV hijo = version_hijo(padre);
    nodoV anterior = NULL;

    while (hijo != NULL && numVersion(hijo) < numActual) {
        anterior = hijo;
        hijo = version_hermano(hijo);
    }
    return anterior;
}

void def_version_texto(texto nuevo_texto, nodoV v) {
    v->linea = nuevo_texto;
}
bool insertar_subversion(nodoV padre,  char* version) {
        int nuevoNum = obtenerUltimoNumero(version);
    
        if (padre->ph == NULL) {
            nodoV nuevo = nuevo_nodo_v();
            nuevo->nombre = strdup(version);
            nuevo->numero = nuevoNum;
            nuevo->padre = padre;
            padre->ph = nuevo;
            return true;
        }
    
        nodoV hijo = padre->ph;
        nodoV anterior = NULL;
        while (hijo != NULL && hijo->numero < nuevoNum) {
            anterior = hijo;
            hijo = hijo->sh;
        }
    

        if ((anterior != NULL && anterior->numero != nuevoNum - 1) ||
            (anterior == NULL && nuevoNum != 1)) {
            return false;
        }
    
        nodoV nuevo = nuevo_nodo_v();
        nuevo->nombre = strdup(version);
        nuevo->numero = nuevoNum;
        nuevo->padre = padre;
        nuevo->sh = hijo;
    
        if (anterior == NULL)
            padre->ph = nuevo;
        else
            anterior->sh = nuevo;
    
        return true;
    }

    nodoV insertar_lista_arboles(nodoV padre, char* version) {
    if (padre == NULL) return NULL;

    int numNuevo = obtenerUltimoNumero((char*)version);

    if (version_hijo(padre) == NULL) {
        nodoV nuevo = nuevo_nodo_v();
        nuevo->nombre = strdup(version);
        nuevo->numero = numNuevo;
        nuevo->padre = padre;
        padre->ph = nuevo;
        cout << "Subversión " << version << " agregada como primer hijo de " << version_nombre(padre) << endl;
        return nuevo;
    }

    nodoV actual = version_hijo(padre);
    nodoV anterior = NULL;

    while (actual != NULL && numVersion(actual) < numNuevo) {
        anterior = actual;
        actual = version_hermano(actual);
    }

    if (actual != NULL && numVersion(actual) == numNuevo) {
        cout << "Ya existe la subversión " << version << endl;
        return NULL;
    }

    if (anterior == NULL && numNuevo != 1) {
        cout << "No existe la subversión anterior a " << version << endl;
        return NULL;
    }
    if (anterior != NULL && numVersion(anterior) != numNuevo - 1) {
        cout << "Falta la subversión anterior antes de " << version << endl;
        return NULL;
    }

   
    nodoV nuevo = nuevo_nodo_v();
    nuevo->nombre = strdup(version);
    nuevo->numero = numNuevo;
    nuevo->padre = padre;

    
    if (anterior == NULL) {
        nuevo->sh = version_hijo(padre);
        padre->ph = nuevo;
    } else {
        nuevo->sh = anterior->sh;
        anterior->sh = nuevo;
    }

    cout << "Subversión " << version << " agregada correctamente." << endl;
    return nuevo;
}

void imprimir_versiones_por_nivel(nodoV v, int nivel){
    if (v == NULL) return;

    // indentación
    for(int i = 0; i < nivel; i++)
        cout << '\t';

    cout << v->nombre << endl;

    imprimir_versiones_por_nivel(version_hijo(v), nivel + 1);


    imprimir_versiones_por_nivel(version_hermano(v), nivel);
}



/*

















void renombrar_prefijo_subarbol(nodoV v, const char* viejo, const char* nuevo) {
    if (v == NULL) return;

    size_t largoViejo = strlen(viejo);

    // Si el nombre del nodo comienza con el prefijo "viejo"
    if (strncmp(v->nombre, viejo, largoViejo) == 0) {
        const char* resto = v->nombre + largoViejo; // parte que sigue después del prefijo viejo

        // Crear nuevo nombre concatenando el prefijo nuevo + resto
        char* nombreNuevo = (char*)malloc(strlen(nuevo) + strlen(resto) + 1);
        if (nombreNuevo == NULL) return; // seguridad

        sprintf(nombreNuevo, "%s%s", nuevo, resto);

        free(v->nombre);
        v->nombre = nombreNuevo;
    }

    // Renombrar recursivamente los hijos y los hermanos
    renombrar_prefijo_subarbol(version_hijo(v), viejo, nuevo);
    renombrar_prefijo_subarbol(version_hermano(v), viejo, nuevo);
}





nodoV corrimiento_hacia_hijos(nodoV padre, int k) {
    if (padre == NULL) return NULL;

    nodoV prev = NULL;
    nodoV cur  = version_hijo(padre);
    while (cur && numVersion(cur) < k) {
        prev = cur;
        cur = version_hermano(cur);
    }

    nodoV nuevo = nuevo_nodo_v();
    char nombre[64];
    sprintf(nombre, "%s.%d", version_nombre(padre), k);
    nuevo->numero = k;
    nuevo->nombre = strdup(nombre);
    nuevo->padre  = padre;

    if (prev == NULL) {
        nuevo->sh = version_hijo(padre);
        padre->ph = nuevo;
    } else {
        nuevo->sh = prev->sh;
        prev->sh = nuevo;
    }

    nuevo->ph = cur;
    if (cur != NULL) {
        nodoV it = cur;
        while (it) {
            it->padre = nuevo;
            it = version_hermano(it);
        }
    }

    // Renumerar y renombrar hijos del nuevo nodo
    int nuevoNum = 1;
    nodoV h = nuevo->ph;
    while (h) {
        int viejo = numVersion(h);
        char viejoPref[64], nuevoPref[64];
        sprintf(viejoPref, "%s.%d", version_nombre(padre), viejo);
        sprintf(nuevoPref, "%s.%d.%d", version_nombre(padre), k, nuevoNum);

        h->numero = nuevoNum;
        free(h->nombre);
        h->nombre = strdup(nuevoPref);

        char viejoSub[80], nuevoSub[80];
        sprintf(viejoSub, "%s.", viejoPref);
        sprintf(nuevoSub, "%s.", nuevoPref);
        renombrar_prefijo_subarbol(version_hijo(h), viejoSub, nuevoSub);

        h = version_hermano(h);
        nuevoNum++;
    }

    return nuevo;
}

void corrimiento_raices_hacia_hijos(Archivo a, int k) {
    if (a == NULL || k < 1) return;

    nodoL bosque = obtener_bosque(a);
    nodoL anterior = NULL;
    nodoL actual = bosque;
    int pos = 1;

    while (actual && pos < k) {
        anterior = actual;
        actual = lista_sig(actual);
        pos++;
    }

    // Nueva raíz
    nodoV nuevaRaiz = nuevo_nodo_v();
    char nombre[16];
    sprintf(nombre, "%d", k);
    nuevaRaiz->numero = k;
    nuevaRaiz->nombre = strdup(nombre);
    nuevaRaiz->padre = NULL;

    nodoL nuevoNodoL ;
    setter_arbol_version(nuevoNodoL , nuevaRaiz);
    if (anterior == NULL) {
        bosque= lista_sig(nuevoNodoL);
        set_bosque(a, nuevoNodoL);
    } else {
        nuevoNodoL->sig = anterior->sig;
        bosque = lista_ant(nuevoNodoL) ;
        lista_sig(nuevoNodoL);
        bosque = 
        anterior->sig = nuevoNodoL;
    }

    // Mover raíces viejas como hijos del nuevo nodo
    if (actual != NULL) {
        nodoV primerHijo = get_arbol_version(actual);
        nuevaRaiz->ph = primerHijo;

        nodoL it = actual;
        while (it) {
            nodoV r = get_arbol_version(it);
            r->padre = nuevaRaiz;
            it = lista_sig(it);
        }
    }

    // Renombrar hijos del nuevo nivel
    nodoV h = nuevaRaiz->ph;
    int nuevoNum = 1;
    while (h) {
        int viejo = numVersion(h);
        char viejoPref[16], nuevoPref[16];
        sprintf(viejoPref, "%d", viejo);
        sprintf(nuevoPref, "%d.%d", k, nuevoNum);

        h->numero = nuevoNum;
        free(h->nombre);
        h->nombre = strdup(nuevoPref);

        char viejoSub[32], nuevoSub[32];
        sprintf(viejoSub, "%s.", viejoPref);
        sprintf(nuevoSub, "%s.", nuevoPref);
        renombrar_prefijo_subarbol(version_hijo(h), viejoSub, nuevoSub);

        h = version_hermano(h);
        nuevoNum++;
    }
}
 


*/














