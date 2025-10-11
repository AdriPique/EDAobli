typedef struct nodo_texto* texto;
void recorrer_e_imprimir_texto(texto t, char* nombre_arch, char* version);
int contador_lineas(texto v);
void insertar(texto &t, int nmr_linea, char* linea_a_insert);
void borrar(texto t, int nmr_linea);