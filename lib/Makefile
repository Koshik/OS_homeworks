all: libhelpers.so libbufio.so
libhelpers.so: helpers.c
	gcc -shared -fPIC -o libhelpers.so helpers.c
libbufio.so: bufio.c
	gcc -shared -fPIC -o libbufio.so bufio.c
