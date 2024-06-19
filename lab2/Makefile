FLAGS = -Wall -lm

all: lab2 broker worker  # Targets for the "all" rule

lab2: lab2.o bmp.o filters.o fbroker.o fworker.o  # Dependencies for lab2
	gcc -o lab2 lab2.o bmp.o filters.o fbroker.o fworker.o $(FLAGS)

broker: broker.o bmp.o filters.o fbroker.o fworker.o  # Dependencies for broker
	gcc -o broker broker.o bmp.o filters.o fbroker.o fworker.o $(FLAGS)

worker: worker.o bmp.o filters.o fworker.o  # Dependencies for worker
	gcc -o worker worker.o bmp.o filters.o fworker.o $(FLAGS)

lab2.o: lab2.c
	gcc -c lab2.c $(FLAGS)

broker.o: broker.c
	gcc -c broker.c $(FLAGS)

worker.o: worker.c
	gcc -c worker.c $(FLAGS)

bmp.o: bmp.c bmp.h
	gcc -c bmp.c $(FLAGS)

filters.o: filters.c filters.h bmp.h
	gcc -c filters.c $(FLAGS)

fbroker.o: fbroker.c fbroker.h bmp.h
	gcc -c fbroker.c $(FLAGS)

fworker.o: fworker.c fworker.h bmp.h
	gcc -c fworker.c $(FLAGS)

clean:
	rm -f lab2 broker worker *.o  # Clean up all executables and object files

