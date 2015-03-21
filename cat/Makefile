all:
	gcc -std=c99 -c cat.c -I ../lib
	gcc -std=c99 cat.o -L../lib -lhelpers -o cat -Wl,-rpath=../lib
