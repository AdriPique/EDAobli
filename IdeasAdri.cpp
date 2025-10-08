#include <iostream>
#include <string.h>
typedef struct Archivo * a; 
typedef struct Versiones * Version;
typedef struct Lineas * Linea;


struct Archivo{
    char* nombre;
    Version versiones;
};
struct Lineas{
    char * texto;
    Linea actual,anterior,siguiente;
    int num_linea;
};

struct Versiones{
    char* nombre;
    Version padre, hijo, hermano;
    Linea linea;
};

typedef enum _retorno TipoRet;

enum _retorno{
OK, ERROR, NO_IMPLEMENTADA
};

int recorrerVersiones(char * version,Archivo a){
    char* parteVersion = strtok(version,".");
    int num1=atoi(parteVersion);
    char* versionact = strtok(a.versiones->nombre,".");//por que me deja usar punto y  no flecha?????
    int num2=atoi(versionact);
    
    if(num1==num2){
        while(parteVersion!=NULL and versionact!=NULL){
            parteVersion = strtok(version,NULL);
            num1=atoi(parteVersion);
            versionact = strtok(a.versiones->nombre,NULL);//por que me deja usar punto y  no flecha?????
            num2=atoi(versionact);
            
        }


    }
}
TipoRet insertar_linea(Archivo &a,char * version,char * linea ,unsigned int nro_linea, char error){

    
    if (strcmp(a.versiones->nombre,version)==0)

        return OK;



}


