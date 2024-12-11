run: build/io.o build/main.o
	cc -Wall -Wextra --pedantic -o run build/main.o build/io.o

build/main.o: src/main.c
	cc -Wall -Wextra --pedantic -c src/main.c -o build/main.o

build/io.o: src/io.c
	cc -Wall -Wextra --pedantic -c src/io.c -o build/io.o

clean:
	rm build/* run
