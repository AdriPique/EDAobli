// Estructuras de Datos y Algoritmos - Obligatorio 2025
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// archivo.c
// Modulo de implementacion de archivo.

#include "texto.h"
#include "archivo.h"
#include <string.h>
#include <iostream>



using namespace std;

struct nodo_archivo{
	char* nombre;
	nodoL bosque;
	
};

struct nodo_lista{
	nodoL siguiente;
	nodoL anterior;
	int posicion;
	nodoV arbolVersion;
};

struct nodo_version{
    nodoV ph;
    nodoV sh;
	nodoV padre;
    char* nombre;
    int nivel;      //Para la referencia cuando tratemos el nombre como un array de enteros,opcional tho.
    int numero;
    texto linea;
};


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



Archivo CrearArchivo(char * nombre){
	Archivo a = new (nodo_archivo);
	a->nombre = new(char[MAX_NOMBRE]);
	strcpy(a->nombre, nombre);
	return a;
}


TipoRet BorrarArchivo(Archivo &a){
// Elimina toda la memoria utilizada por el archivo y asigna NULL al puntero a.
// Se asume como precondición que a referencia a un archivo (en particular a es distinto a NULL).
// Esta operación se ejecuta al final de una sesión de trabajo con un archivo.
	nodoL aux=a->bosque;
	nodoL aux2=aux;
	while(aux!=NULL){
		borrar_arbol(aux->arbolVersion);
		aux=aux->siguiente;
		delete aux2;
		aux2=aux;
	}
	delete a;
	a=NULL;
	return OK;
}


TipoRet CrearVersion(Archivo &a, char* version, char* error){
// Crea una nueva versión del archivo si la versión especificada cumple con las siguientes reglas:
// - El padre de la nueva versión a crear ya debe existir. Por ejemplo, si creo la versión 2.15.1, la versión 2.15 ya debe existir.
// Las versiones del primer nivel no siguen esta regla, ya que no tienen versión padre.
// - No pueden quedar “huecos” entre versiones hermanas. Por ejemplo, si creamos la versión 2.15.3, las versiones 2.15.1 y 2.15.2 ya deben existir.
// Ver ejemplo en la letra.

	cout << "VERSION A INSERTAR: " << version << endl;

	return NO_IMPLEMENTADA;
}

TipoRet BorrarVersion(Archivo &a, char * version){
// Elimina una versión del archivo si la version pasada por parámetro existe. En otro caso la operación quedará sin efecto.
// Si la versión a eliminar posee subversiones, éstas deberán ser eliminadas también, así como el texto asociado a cada una de las versiones.
// No deben quedar números de versiones libres sin usar. Por lo tanto cuando se elimina una versión, las versiones hermanas que le siguen deben decrementar su numeración (así también sus subversiones dependientes). Por ejemplo, si existen las versiones 2.15.1, 2.15.2 y 2.15.3, y elimino la 2.15.1, la versión 2.15.2 y la 2.15.3 pasan a ser 2.15.1 y 2.15.2 respectivamente, esto incluye a todas las subversiones de estas versiones.

	return NO_IMPLEMENTADA;
}

TipoRet MostrarVersiones(Archivo a){
// FORMATO: En primer lugar muestra el nombre del archivo. Después de una línea en blanco lista todos las versiones del archivo
// ordenadas por nivel jerárquico e indentadas según muestra el ejemplo publicado en la letra (cada nivel está indentado por un tabulador).
	cout << a->nombre << endl << endl;


	return NO_IMPLEMENTADA;
}

TipoRet InsertarLinea(Archivo &a, char* version, char* linea, unsigned int nroLinea, char* error){
// Esta función inserta una linea de texto a la version parámetro en la posición nroLinea.
// El número de línea debe estar entre 1 y n+1, siendo n la cantidad de líneas del archivo. Por ejemplo, si el texto tiene 7 líneas, se podráinsertar en las posiciones 1 (al comienzo) a 8 (al final).
// Si se inserta en un número de línea existente, ésta y las siguientes líneas se correrán hacia adelante (abajo) dejando el espacio para la nueva línea.
// No se puede insertar una línea en una versión que tenga subversiones.
// Notar que el crear un archivo, éste no es editable hasta que no se crea al menos una versión del mismo. Sólo las versiones de un archivo son editables (se pueden insertar o suprimir líneas), siempre que no tengan subversiones creadas.
// En caso que TipoRet sea ERROR, en error se debe cargar cuál es el mismo.
	nodoV aux=version_existe(a, version);
	if(aux==NULL){
		error = strdup("La versión estipulada no existe");
		cout << error << endl;
		return ERROR;
	} else if(aux->ph!=NULL){
		error = strdup("La version a modificar tiene subversiones. No se puede insertar la línea.");
		cout << error << endl;
		return ERROR;
	} else {
		if(contador_lineas(aux->linea)+1 < nroLinea || nroLinea < 1){
			error = strdup("Número de línea no válido.");
			cout << error << endl;
			return ERROR;
		} else {
			insertar(aux->linea, nroLinea, linea);	
			return OK;
		}
	}
}

TipoRet BorrarLinea(Archivo &a, char * version, unsigned int nroLinea, char * error){
// Esta función elimina una línea de texto de la version del archivo a en la posición nroLinea.
// El número de línea debe estar entre 1 y n, siendo n la cantidad de líneas del archivo. Por ejemplo, si el texto tiene 7 líneas, se podrán eliminar líneas de las posiciones 1 a 7.
// Cuando se elimina una línea, las siguientes líneas se corren, decrementando en una unidad sus posiciones para ocupar el lugar de la línea borrada.
// No se puede borrar una línea de una versión que tenga subversiones creadas.
// En caso que TipoRet sea ERROR, en error se debe cargar cuál es el mismo.
	nodoV aux=version_existe(a, version);
	if(aux==NULL){
		error = strdup("La versión estipulada no existe");
		cout << error << endl;
		return ERROR;
	} else if(aux->ph!=NULL){
		error= strdup("La version a modificar tiene subversiones. No se puede eliminar la línea.");
		cout << error << endl;
		return ERROR;
	} else {
		if(contador_lineas(aux->linea) < nroLinea || nroLinea < 1){
			error= strdup("Número de línea no válido.");
			cout << error << endl;
			return ERROR;
		} else {
			eliminar_linea(aux->linea, nroLinea);	
			return OK;
		}
	}


	return NO_IMPLEMENTADA;
}

TipoRet MostrarTexto(Archivo a, char * version){
// Esta función muestra el texto completo de la version, teniendo en cuenta los cambios realizados en dicha versión y en las versiones ancestras, de la cual ella depende.
	nodoV aux=version_existe(a, version);
	if(aux==NULL){						
		cout << "La versión especificada no existe" << endl;
		return ERROR;
	} else {
		recorrer_e_imprimir_texto(aux->linea, a->nombre, aux->nombre);
		return OK;
	}
}


TipoRet MostrarCambios(Archivo a, char * version){
// Esta función muestra los cambios que se realizaron en el texto de la version parámetro, sin incluir los cambios realizados en las versiones ancestras de la cual dicha versión depende.

	return NO_IMPLEMENTADA;
}

TipoRet Iguales(Archivo a, char * version1, char * version2, bool &iguales){
// Esta función asigna al parámetro booleano (iguales) el valor true si ambas versiones (version1 y version2) del archivo tienen exactamente el mismo texto, y false en caso contrario.

	return NO_IMPLEMENTADA;
}

TipoRet VersionIndependiente(Archivo &a, char * version){
// Esta función crea una nueva versión al final del primer nivel con todos los cambios de la version especificada y de sus versiones ancestras. La versión que se crea debe ser independiente de cualquier otra versión.
// Por ejemplo, si creamos una versión independiente a partir de la 2.11.3, entonces se crea una nueva versión al final del primer nivel (si existen las versiones 1, 2, 3 y 4, entonces se crea la 5) con los cambios realizados a las versiones 2, 2.11 y 2.11.3.

	return NO_IMPLEMENTADA;
}




