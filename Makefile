main: main.c io.o
	cc -o main main.c io.o

io.o: io.c
	cc -c io.c
