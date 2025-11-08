// Estructuras de Datos y Algoritmos - Obligatorio 2025
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// main.c
// Programa Principal Obligatorio

#include "archivo.h"
#include <string.h>
#include <stdio.h> 
#include <iostream>
#include <stdlib.h>
#include "texto.h"
using namespace std;


int main(){
	char * nombre = new(char[MAX_NOMBRE]);
	char * comando = new(char[MAX_COMANDO]);
	char * error = new(char[MAX_COMANDO]);
	TipoRet retorno;
	bool ejecutado = false;
	char * pch, * pch1, * pch2;
	
	cout << "Inserte el nombre del archivo\n> ";
	cin >> nombre;
	
	Archivo a = CrearArchivo(nombre);
	cout << " - Archivo \"" << nombre << "\" creado.\n";
	
	fgets(comando, MAX_COMANDO, stdin);
	// consumo el resto de la linea

	bool salir = false;
	bool iguales;
	
	do{
		cout << "\tCrearVersion(version)\n";
		cout << "\tBorrarVersion(version)\n";
		cout << "\tMostrarVersiones()\n";
		cout << "\tInsertarLinea(version, linea, nroLinea)\n";
		cout << "\tBorrarLinea(version, nroLinea)\n";
		cout << "\tMostrarTexto(version)\n";
		cout << "\tMostrarCambios(version)\n";
		cout << "\tIguales(version1, version2)\n";
		cout << "\tVersionIndependiente(version)\n";
		cout << "\tsalir\n";
		
		strcpy (error, ""); // Resetea el mensaje de error.
		
		fflush( stdin );
		ejecutado = false;
		cout << "> ";		

		fgets (comando, MAX_COMANDO, stdin); // leo la linea entera del comando. 
		pch = strtok (comando,"( ,)\n");

		if (strcasecmp (pch, "CrearVersion") == 0){
			pch = strtok (NULL, "( ,)\n");
			if (pch != NULL){
				retorno = CrearVersion(a,  pch, error);
				ejecutado = true;
			}else
				cout << " - ERROR: Faltan Parametros.\n";
		}else if (strcasecmp (pch, "BorrarVersion") == 0){
			pch = strtok (NULL, "( ,)\n");
			if (pch != NULL){
				retorno = BorrarVersion(a, pch);
				ejecutado = true;
			}else
				cout << " - ERROR: Faltan Parametros.\n";
		}else if (strcasecmp (pch, "MostrarVersiones") == 0){
			retorno = MostrarVersiones(a);
			ejecutado = true;
		}else if (strcasecmp (pch, "InsertarLinea") == 0){
			pch = strtok (NULL, "( ,)\n");
			if (pch != NULL){
				pch1 = strtok (NULL, "(,)\n");
				if (pch1 != NULL){
					pch2 = strtok (NULL, "( ,)\n");
					if (pch2 != NULL){
						retorno = InsertarLinea(a, pch, pch1, atoi (pch2), error);
						ejecutado = true;
					}else
						cout << " - ERROR: Faltan Parametros.\n";
				}else
					cout << " - ERROR: Faltan Parametros.\n";
			}else
				cout << " - ERROR: Faltan Parametros.\n";
		}else if (strcasecmp (pch, "BorrarLinea") == 0){
			pch = strtok (NULL, "( ,)\n");
			if (pch != NULL){
				pch1 = strtok (NULL, "( ,)\n");
				if (pch1 != NULL){
					retorno = BorrarLinea(a, pch, atoi(pch1), error);
					ejecutado = true;
				}else
					cout << " - ERROR: Faltan Parametros.\n";
			}else
				cout << " - ERROR: Faltan Parametros.\n";
		}else if (strcasecmp (pch, "MostrarTexto") == 0){
			pch = strtok (NULL, "( ,)\n");
			if (pch != NULL){
				retorno = MostrarTexto(a, pch);
				ejecutado = true;
			}else
				cout << " - ERROR: Faltan Parametros.\n";
		}else if (strcasecmp (pch, "MostrarCambios") == 0){
			pch = strtok (NULL, "( ,)\n");
			if (pch != NULL){
				retorno = MostrarCambios(a, pch);
				ejecutado = true;
			}else
				cout << " - ERROR: Faltan Parametros.\n";
		}else if (strcasecmp (pch, "Iguales") == 0){
			pch = strtok (NULL, "( ,)\n");
			if (pch != NULL){
				pch1 = strtok (NULL, "( ,)\n");
				if (pch1 != NULL){
					retorno = Iguales(a, pch, pch1, iguales);
					ejecutado = true;
					if (retorno == OK){
						if (iguales)
							cout << " - Las versiones son iguales.\n";
						else
							cout << " - Las versiones son distintas.\n";
					}
				}else
					cout << " - ERROR: Faltan Parametros.\n";
			}else
				cout << " - ERROR: Faltan Parametros.\n";
		}else if (strcasecmp (pch, "VersionIndependiente") == 0){
			pch = strtok (NULL, "( ,)\n");
			if (pch != NULL){
				retorno = VersionIndependiente(a, pch);
				ejecutado = true;
			}else
				cout << " - ERROR: Faltan Parametros.\n";
		}else if (strcasecmp (pch, "salir") == 0){
			cout << "\t- CHAUUUUU!!!\n\n";
			salir = true;
		}else{
			cout << " - Comando Incorrecto.\n\n";
			retorno = ERROR;
		}
		if (ejecutado){
				if (retorno == OK)
					cout << " - OK\n\n";
				else if (retorno == ERROR)
					cout << " - ERROR " << error << "\n\n";
				else
					cout << " - NO IMPLEMENTADA\n\n";
		}

	}while (!salir);
	
	retorno = BorrarArchivo(a);
	if (retorno == OK)
		cout << " - Archivo \"" << nombre << "\" borrado con exito.\n\n";
	else if (retorno == ERROR)
		cout << " - Error al borrar el archivo \"" << nombre << "\".\n\n";
	else
		cout << " - Operacion BorrarArchivo NO IMPLEMENTADA\n\n";
	
	delete [] nombre;
	delete [] comando;
	delete [] error;
}
