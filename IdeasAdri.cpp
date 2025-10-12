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
    int numero;
};

typedef enum _retorno TipoRet;

enum _retorno{
OK, ERROR, NO_IMPLEMENTADA
};

bool tieneHijo(Versiones v){
    return(v.hijo!=NULL);
}



char versionNumerica(Versiones v ){
    char * nodo=new char; 

}

/*Archivo recorrerVersiones(char * version,Archivo a){
    char* parteVersion = strtok(version,".");
    int num1=atoi(parteVersion);
    int num2=a.versiones->numero;// LA CONCHA DEL PUNTO
    while(parteVersion!=NULL){
        if(num1==num2){
            parteVersion=strtok(NULL,".");
            num1=atoi(parteVersion);
            if (num1 > a.versiones->hijo->numero){
                num2=a.versiones->hermano->numero;
            }else if(num1 > a.versiones->hermano->numero){
                num2=a.versiones->hijo->numero;
            }
        }
    }
    
}*/
/*int tokenVersion( char * version){
    //te devuelve de a un elemento numerico
    
    char *token;
    char *tokens[20]; 
    int i = 0;
    
    token = strtok(version, "."); 
    while (token != NULL && i < 10) {
        tokens[i] = token; 
        i++;
        token = strtok(NULL, ".");
    }
    int cabezaVersion=atoi(tokens[0]);
    
    return cabezaVersion;
}*/
Version ExisteVersion(Archivo a, char version[]){
    //Pre: Saber que la version que queremos trabajar no es la primera 
    //Post: Si existe version te devuelve la version en la que queremos trabajar
    //Si no existe te devuelve la Primera version 
    
    Archivo aux= a;
    Version quiero= aux.versiones;
    int i=0;
    bool existe= false;
    char actual[20];
    while(version[i]!= NULL || existe == false){
        
        if(quiero->numero==version[i]-48){//si el numero es igual nos metemos en ese puntero || probando con codigo ASCII 
            actual[i]=quiero->numero+48;
            actual[i+1]='.';
            i=i+2; // nos paramos en el siguiente valor del string de aux
            if(strcmp(actual, version)==0){//si actual y version son iguales existe version y cortamo
                existe= true;
            }
        }else if((quiero->hermano!=NULL)&&( quiero->hermano->numero==version[i]-48)){ //si la version en la que estamos parados tiene un hermano y esta version hermana nos sirve nos movemos
            quiero=quiero->hermano;// solo me muevo en sub versiones (hacia la derecha) si el siguiente numero me sirve

        }else if((quiero->hijo!=NULL)&& (quiero->hijo->numero>=version[i]-48)){//siempre que el hijo sea mayor o igual sigo bajando
            quiero=quiero->hijo;
        }
        else{
            i=i+2;//si no existe la version pero sigue habiendo que recorrer el string version lo recorremos 
        }

    }      
    if(existe)
        return quiero;
    else
        return aux.versiones;
        
}
TipoRet insertar_linea(Archivo &a,char * version,char * linea ,unsigned int nro_linea, char error){

    
    if (strcmp(a.versiones->nombre,version)==0)

        return OK;



}


