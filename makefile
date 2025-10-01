todo: main.o archivo.o
	g++ -Wall -o main main.o archivo.o
main.o: main.c
	g++ -Wall -c main.c
archivo.o: archivo.h archivo.c
	g++ -Wall -c archivo.c
limpiar:
	rm -f main
	rm -f *.o

