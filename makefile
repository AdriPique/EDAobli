mi_programa: main.o archivo.o texto.o versiones.o lista_arboles.o
	g++ -Wall -o mi_programa main.o archivo.o texto.o versiones.o lista_arboles.o

main.o: main.cpp
	g++ -Wall -c main.cpp

archivo.o: archivo.h archivo.cpp
	g++ -Wall -c archivo.cpp

texto.o: texto.h texto.cpp
	g++ -Wall -c texto.cpp

versiones.o: versiones.h versiones.cpp
	g++ -Wall -c versiones.cpp

lista_arboles.o: lista_arboles.h lista_arboles.cpp
	g++ -Wall -c lista_arboles.cpp

limpiar:
	rm -f mi_programa
	rm -f *.o
