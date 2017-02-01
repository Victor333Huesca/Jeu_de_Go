CC=g++ -std=c++11

CFLAGS=-Wall -c

all: GoSolver

GoSolver: Etat.o Goban.o main.o
	$(CC) Etat.o Goban.o main.o -o GoSolver

Etat.o: Etat.cpp Etat.h
	$(CC) $(CFLAGS) Etat.cpp

Goban.o: Goban.cpp Goban.h
	$(CC) $(CFLAGS) Goban.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm -rf *o GoSolver
