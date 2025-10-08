todo: main.o archivo.o
	g++ -Wall -o main main.o archivo.o
main.o: main.cpp
	g++ -Wall -c main .cpp
archivo.o: archivo.h archivo.cpp
	g++ -Wall -c archivo.cpp
limpiar:
	rm -f main
	rm -f *.o

