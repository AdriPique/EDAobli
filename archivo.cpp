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
#include <cstdio>
using namespace std;


struct nodo_archivo{
	char* nombre;
	nodoL bosque;
	
};

//Retorna un puntero al bosque de un archivo
nodoL obtener_bosque(Archivo a){
	return a->bosque;
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


TipoRet CrearVersion(Archivo &a, char* version, char* error){
// Crea una nueva versión del archivo si la versión especificada cumple con las siguientes reglas:
// - El padre de la nueva versión a crear ya debe existir. Por ejemplo, si creo la versión 2.15.1, la versión 2.15 ya debe existir.
// Las versiones del primer nivel no siguen esta regla, ya que no tienen versión padre.
// - No pueden quedar “huecos” entre versiones hermanas. Por ejemplo, si creamos la versión 2.15.3, las versiones 2.15.1 y 2.15.2 ya deben existir.
// Ver ejemplo en la letra.

}

static void actualizar_nombre_nodo(nodoV v){
    if (v==NULL)
    {
        return;
    }

    if(v->nombre==NULL){
		v->nombre = new char[MAX_NOMBRE];
    }

    if (v->padre != NULL)
    {
		snprintf(v->nombre, MAX_NOMBRE, "%s.%d", v->padre->nombre, v->numero);
    } else {
		snprintf(v->nombre, MAX_NOMBRE, "%d", v->numero);
    }
	v->nombre[MAX_NOMBRE-1] = '\0';
	
}
static void actualizar_subarbol(nodoV v){
	if (v==NULL){
		return;
	}
	actualizar_nombre_nodo(v);
	nodoV hijo = version_hijo(v);
	while (hijo!=NULL){
		hijo->padre=v;
		actualizar_subarbol(hijo);
		hijo=version_hermano(hijo);
	}
}
static void renumerar_hijos(nodoV padre){
	if(padre==NULL){
		return;
	}
	nodoV hijo=version_hijo(padre);
	int inidice = 1;
	while(hijo!=NULL){
		hijo->numero=inidice++;
		hijo->padre=padre;
		actualizar_subarbol(hijo);
		hijo=version_hermano(hijo);
	}
}
static void renumerar_bosque(Archivo a){
	if(a == NULL){
		return;
	}
	nodoL actual = obtener_bosque(a);
	int indice = 1;
	while(actual != NULL){
		lista_set_posicion(actual, indice);
		nodoV raiz = get_arbol_version(actual);
		if(raiz != NULL){
			raiz->numero = indice;
			raiz->padre = NULL;
			actualizar_subarbol(raiz);
		}
		actual = lista_sig(actual);
		indice++;
	}
}

TipoRet BorrarVersion(Archivo &a, char * version){
// Elimina una versión del archivo si la version pasada por parámetro existe. En otro caso la operación quedará sin efecto.
// Si la versión a eliminar posee subversiones, éstas deberán ser eliminadas también, así como el texto asociado a cada una de las versiones.
// No deben quedar números de versiones libres sin usar. Por lo tanto cuando se elimina una versión, las versiones hermanas que le siguen deben decrementar su numeración (así también sus subversiones dependientes). Por ejemplo, si existen las versiones 2.15.1, 2.15.2 y 2.15.3, y elimino la 2.15.1, la versión 2.15.2 y la 2.15.3 pasan a ser 2.15.1 y 2.15.2 respectivamente, esto incluye a todas las subversiones de estas versiones.

	if(a==NULL || version==NULL){
                return ERROR;
        }

        nodoV objetivo = encontrar_version(a, version);
        if(objetivo==NULL){
                return ERROR;
        }

        nodoV padre = version_padre(objetivo);
        if(padre==NULL){
                nodoL actual = obtener_bosque(a);
                nodoL anterior = NULL;
                while(actual!=NULL && get_arbol_version(actual)!=objetivo){
                        anterior = actual;
                        actual = lista_sig(actual);
                }
                if(actual==NULL){
                        return ERROR;
                }
                nodoL siguiente = lista_sig(actual);
                if(anterior==NULL){
                        a->bosque = siguiente;
                } else {
                        lista_set_sig(anterior, siguiente);
                }
                if(siguiente!=NULL){
                        lista_set_ant(siguiente, anterior);
                }
                lista_set_sig(actual, NULL);
                lista_set_ant(actual, NULL);
                objetivo->sh = NULL;
                objetivo->padre = NULL;
                borrar_arbol(objetivo);
                delete actual;
                renumerar_bosque(a);
        } else {
                nodoV hijo = version_hijo(padre);
                nodoV anterior = NULL;
                while(hijo!=NULL && hijo!=objetivo){
                        anterior = hijo;
                        hijo = version_hermano(hijo);
                }
                if(hijo==NULL){
                        return ERROR;
                }
                nodoV siguiente = version_hermano(objetivo);
                if(anterior==NULL){
                        padre->ph = siguiente;
                } else {
                        anterior->sh = siguiente;
                }
                if(siguiente!=NULL){
                        siguiente->padre = padre;
                }
                objetivo->sh = NULL;
                objetivo->padre = NULL;
                borrar_arbol(objetivo);
                renumerar_hijos(padre);
        }

        return OK;
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
	nodoV aux=encontrar_version(a, version);
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
			insertar(auxT, nroLinea, linea);	
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
	nodoV aux=encontrar_version(a, version);
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
			eliminar_linea(a_borrar, nroLinea);
				
			return OK;
		}
	}
}

TipoRet MostrarTexto(Archivo a, char * version){
// Esta función muestra el texto completo de la version, teniendo en cuenta los cambios realizados en dicha versión y en las versiones ancestras, de la cual ella depende.
	nodoV aux=encontrar_version(a, version);
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
    nodoV aux = encontrar_version(a, version);
    if (aux == NULL) {
        cout << "La versión especificada no existe" << endl;
        return ERROR;
    }

    cout << a->nombre << " - " << version_nombre(aux) << endl << endl;

    // Si no hay texto asociado ni modificaciones
    if (version_linea(aux) == NULL) {
        cout << "No se realizaron modificaciones" << endl;
        return OK;
    }

    // Como todavía no hay estructura de seguimiento de cambios (solo el texto final),
    // mostramos todas las líneas como inserciones locales (IL) para testeo del flujo.
    texto t = aux->linea;
	int num= numerolinea(t);
	char *s=new(char); 
	linea(t,s);
    if (t == NULL) {
        cout << "No se realizaron modificaciones" << endl;
    } else {
        while (t != NULL) {
            cout << "IL\t" << num << "\t" << s << endl;
             t = siguientelinea(t); 
			 num=numerolinea(t);
			 linea(t,s);

        }
    }

    return OK;

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




