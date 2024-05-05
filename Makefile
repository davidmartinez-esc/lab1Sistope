FLAGS = -Wall -lm

main: lab1.c funciones.o
	gcc -o lab1 lab1.c funciones.o $(FLAGS)

funciones.o: funciones.c
	gcc -c funciones.c $(FLAGS)

clear:
	rm -f main *.o
