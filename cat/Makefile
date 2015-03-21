all: cat.o
	gcc -std=c99 cat.o -L../lib -lhelpers -Wl,-rpath=../lib -o cat 
cat.o: cat.c
	gcc -std=c99 -c cat.c -I ../lib
