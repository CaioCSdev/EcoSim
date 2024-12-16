run: build/io.o build/main.o build/movement.o build/simulation.o
	cc -fopenmp -g -Wall -Wextra --pedantic -o run build/main.o build/io.o build/movement.o build/simulation.o

build/main.o: src/main.c
	cc -fopenmp -g -Wall -Wextra --pedantic -c src/main.c -o build/main.o

build/io.o: src/io.c
	cc -fopenmp -g -Wall -Wextra --pedantic -c src/io.c -o build/io.o

build/movement.o: src/movement.c
	cc -fopenmp -g -Wall -Wextra --pedantic -c src/movement.c -o build/movement.o

build/simulation.o: src/simulation.c
	cc -fopenmp -g -Wall -Wextra --pedantic -c src/simulation.c -o build/simulation.o

test:
	cc -fopenmp -g -Wall -Wextra --pedantic -o test tests/movement_test.c build/movement.o
	./test

clean:
	rm build/* run test

.PHONY: clean test
