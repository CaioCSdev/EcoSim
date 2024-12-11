all: build/io.o build/main.o
	cc -o run build/main.o build/io.o

build/main.o: src/main.c
	cc -c src/main.c -o build/main.o

build/io.o: src/io.c
	cc -c src/io.c -o build/io.o

clean:
	rm build/* run
