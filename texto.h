typedef struct nodo_texto* texto;
texto nuevo_nodo_texto();
void recorrer_e_imprimir_texto(texto t, char* nombre_arch, char* version);
int contador_lineas(texto v);
void insertar(texto &t, int nmr_linea, char* linea_a_insert);
void eliminar_linea(texto t, int nmr_linea);
void eliminar_texto(texto t);