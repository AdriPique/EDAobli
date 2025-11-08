mi_programa: main.o archivo.o texto.o 
	g++ -Wall -o main main.o archivo.o texto.o -o mi_programa
main.o: main.cpp
	g++ -Wall -c main.cpp
archivo.o: archivo.h archivo.cpp
	g++ -Wall -c archivo.cpp
texto.o: texto.cpp
	g++ -Wall -c texto.cpp
limpiar:
	rm -f mi_programa
	rm -f *.o
