all: helpers.o
	gcc -shared -o libhelpers.so helpers.o
helpers.o: helpers.h helpers.c
	gcc -std=c99 -fPIC -c helpers.c
clean:
	rm *.o
