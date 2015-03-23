all: filter.o
	gcc -std=c99 filter.o -L../lib -lhelpers -Wl,-rpath=../lib -o filter
filter.o: filter.c
	gcc -std=c99 -c filter.c -I ../lib
