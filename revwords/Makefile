all: revwords.o
	gcc -std=c99 revwords.o -L../lib -lhelpers -Wl,-rpath=../lib -o revwords
revwords.o: revwords.c
	gcc -std=c99 -c revwords.c -I ../lib
