funciones.o: funciones.h funciones.cpp
	g++ -Wall -g3 -c funciones.cpp

main: main.cpp funciones.o
	g++ -Wall -g3 -o main main.cpp funciones.o

.PHONY: clean
clean:
	rm -fr *.o main