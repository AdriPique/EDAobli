// Estructuras de Datos y Algoritmos - Obligatorio 2025
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// archivo.c
// Modulo de implementacion de archivo.

#include "texto.h"
#include "archivo.h"
#include "versiones.h"
#include "lista_arboles.h"
#include <string.h>
#include <iostream>
using namespace std;
/*
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
*/

struct nodo_archivo{
	char* nombre;
	nodoL bosque;
	
};

//Retorna un puntero al bosque de un archivo
nodoL obtener_bosque(Archivo a){
	return a->bosque;
}

void set_bosque(Archivo a, nodoL l){
	a->bosque=l;
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
		borrar_arbol(get_arbol_version(aux));
		aux=lista_sig(aux);
		delete aux2;
		aux2=aux;
	}
	delete a;
	a=NULL;
	return OK;
}


TipoRet CrearVersion(Archivo &a, char* version, char* error)
{
    if (version == NULL || version[0] == '\0') {
        error = strdup("Versión vacía.");
        return ERROR;
    }

    // Copia defensiva
    char v1[128]; strncpy(v1, version, sizeof(v1)); v1[sizeof(v1)-1] = '\0';
    char v2[128]; strncpy(v2, version, sizeof(v2)); v2[sizeof(v2)-1] = '\0';

    bool esRaizVer = esRaiz(v1);

    // → Raíces NO tienen padre
    if (esRaizVer) {

        // ¿Existe raíz igual? → corresponde corrimiento en lista de raíces
        if (existeRaiz(a, v1)) {

            if (!corrimientoRaices(a, v1)) {
                error = strdup("No fue posible desplazar raíces.");
                return ERROR;
            }

            // Ahora se crea normalmente al final del corrimiento
            if (!crearRaiz(a, v2)) {
                error = strdup("No se pudo crear la raíz.");
                return ERROR;
            }
        }
        else {
            // Verificar que no haya “hueco” → versión 3 no si falta 2
            if (!padreRaizValido(a, v1)) {
                error = strdup("No existe raíz anterior.");
                return ERROR;
            }

            if (!crearRaiz(a, v2)) {
                error = strdup("No se pudo crear la raíz.");
                return ERROR;
            }
        }

        return OK;
    }
	// → SUBVERSIÓN
    nodoV padre = buscarPadre(a, v2);
    if (padre == NULL) {
        error = strdup("El padre no existe.");
        return ERROR;
    }

    // ¿Existe esta subversión?
    nodoV existe = encontrarVersion(a, v1);

    int numeroNuevo = obtenerUltimoNumero(v1);

    // Si existe → corrimiento
    if (existe != NULL) {

        if (!corrimientoHijos(padre, numeroNuevo)) {
            error = strdup("No se pudo desplazar hermanos.");
            return ERROR;
        }

        // Crear nueva subversión en posición que quedó libre
        if (insertarSubversionNueva(padre, v2) == NULL) {
            error = strdup("Error al crear nueva subversión.");
            return ERROR;
        }

        return OK;
    }

    // No existe → alta normal
    if (!verificarHuecoHermano(padre, numeroNuevo)) {
        error = strdup("Hueco en hermanos.");
        return ERROR;
    }

    if (insertarSubversionNueva(padre, v2) == NULL) {
        error = strdup("Error al crear la versión.");
        return ERROR;
    }

    return OK;
}



TipoRet BorrarVersion(Archivo &a, char * version){
// Elimina una versión del archivo si la version pasada por parámetro existe. En otro caso la operación quedará sin efecto.
// Si la versión a eliminar posee subversiones, éstas deberán ser eliminadas también, así como el texto asociado a cada una de las versiones.
// No deben quedar números de versiones libres sin usar. Por lo tanto cuando se elimina una versión, las versiones hermanas que le siguen deben decrementar su numeración (así también sus subversiones dependientes). Por ejemplo, si existen las versiones 2.15.1, 2.15.2 y 2.15.3, y elimino la 2.15.1, la versión 2.15.2 y la 2.15.3 pasan a ser 2.15.1 y 2.15.2 respectivamente, esto incluye a todas las subversiones de estas versiones.

	return NO_IMPLEMENTADA;
}
// FORMATO: En primer lugar muestra el nombre del archivo. Después de una línea en blanco lista todos las versiones del archivo
// ordenadas por nivel jerárquico e indentadas según muestra el ejemplo publicado en la letra (cada nivel está indentado por un tabulador).

TipoRet MostrarVersiones(Archivo a){
    if (a == NULL)
        return ERROR;

    cout << a->nombre << endl << endl;

    nodoL lista = obtener_bosque(a);

    if (lista == NULL){
        cout << "(No hay versiones creadas)" << endl;
        return OK;
    }

    // recorrer raíces del bosque
    while (lista != NULL){
        nodoV raiz = get_arbol_version(lista);
        imprimir_versiones_por_nivel(raiz, 0);
        lista = lista_sig(lista);
    }

    return OK;
}

TipoRet InsertarLinea(Archivo &a, char* version, char* linea, unsigned int nroLinea, char* error){
// Esta función inserta una linea de texto a la version parámetro en la posición nroLinea.
// El número de línea debe estar entre 1 y n+1, siendo n la cantidad de líneas del archivo. Por ejemplo, si el texto tiene 7 líneas, se podráinsertar en las posiciones 1 (al comienzo) a 8 (al final).
// Si se inserta en un número de línea existente, ésta y las siguientes líneas se correrán hacia adelante (abajo) dejando el espacio para la nueva línea.
// No se puede insertar una línea en una versión que tenga subversiones.
// Notar que el crear un archivo, éste no es editable hasta que no se crea al menos una versión del mismo. Sólo las versiones de un archivo son editables (se pueden insertar o suprimir líneas), siempre que no tengan subversiones creadas.
// En caso que TipoRet sea ERROR, en error se debe cargar cuál es el mismo.
	nodoV aux=encontrarVersion(a, version);
	texto auxT= version_texto(aux); 
	if(aux==NULL){
		error = strdup("La version estipulada no existe");
		cout << error << endl;
		return ERROR;
	} else if(version_hijo(aux)!=NULL){
		error = strdup("La version a modificar tiene subversiones. No se puede insertar la linea.");
		cout << error << endl;
		return ERROR;
	} else {
		if(contador_lineas(auxT)+1 < nroLinea || nroLinea < 1){
			error = strdup("Numero de linea no valido.");
			cout << error << endl;
			return ERROR;
		} else {
			insertar(auxT, nroLinea, linea, aux);
			def_version_texto(auxT, aux);	
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
	nodoV aux=encontrarVersion(a, version);
	if(aux==NULL){
		error = strdup("La version estipulada no existe");
		cout << error << endl;
		return ERROR;
	} else if(version_hijo(aux)!=NULL){
		error= strdup("La version a modificar tiene subversiones. No se puede eliminar la linea.");
		cout << error << endl;
		return ERROR;
	} else {
		if(contador_lineas(version_texto(aux)) < nroLinea || nroLinea < 1){
			error= strdup("Numero de linea no valido.");
			cout << error << endl;
			return ERROR;
		} else {
			texto a_borrar=version_texto(aux);
			eliminar_linea(a_borrar, nroLinea, aux);
				
			return OK;
		}
	}
}

TipoRet MostrarTexto(Archivo a, char * version){
// Esta función muestra el texto completo de la version, teniendo en cuenta los cambios realizados en dicha versión y en las versiones ancestras, de la cual ella depende.
	nodoV aux=encontrarVersion(a, version);
	if(aux==NULL){						
		cout << "La version especificada no existe" << endl;
		return ERROR;
	} else {
		recorrer_e_imprimir_texto(version_texto(aux), a->nombre, version_nombre(aux));
		return OK;
	}
}


TipoRet MostrarCambios(Archivo a, char * version){
// Esta función muestra los cambios que se realizaron en el texto de la version parámetro, sin incluir los cambios realizados en las versiones ancestras de la cual dicha versión depende.
// Muestra los cambios realizados en la versión respecto a su padre directo.
    nodoV aux = encontrarVersion(a, version);
    if (aux == NULL) {
        cout << "La versión especificada no existe" << endl;
        return ERROR;
    }

    cout << a->nombre << " - " << version_nombre(aux) << endl << endl;

    // Si no hay texto asociado ni modificaciones
    if (version_linea(aux) == NULL) {
        cout << "No se realizaron modificaciones" << endl;
        return OK;
    } else {
		imprimir_historial(aux);
    	return OK;
	}
}



TipoRet Iguales(Archivo a, char * version1, char * version2, bool &iguales){
// Esta función asigna al parámetro booleano (iguales) el valor true si ambas versiones (version1 y version2) del archivo tienen exactamente el mismo texto, y false en caso contrario.
iguales = false;

	nodoV primera = encontrarVersion(a, version1);
	if(primera == NULL){
		cout << "La version estipulada no existe" << endl;
		return ERROR;
	}

	nodoV segunda = encontrarVersion(a, version2);
	if(segunda == NULL){
		cout << "La version estipulada no existe" << endl;
		return ERROR;
	}

	iguales = textos_iguales(version_texto(primera), version_texto(segunda));
	return OK;
}

TipoRet VersionIndependiente(Archivo &a, char * version){
// Esta función crea una nueva versión al final del primer nivel con todos los cambios de la version especificada y de sus versiones ancestras. La versión que se crea debe ser independiente de cualquier otra versión.
// Por ejemplo, si creamos una versión independiente a partir de la 2.11.3, entonces se crea una nueva versión al final del primer nivel (si existen las versiones 1, 2, 3 y 4, entonces se crea la 5) con los cambios realizados a las versiones 2, 2.11 y 2.11.3.

	return NO_IMPLEMENTADA;
}




