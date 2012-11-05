CC=gcc
CFLAGS=-Wall -Werror -pedantic -std=gnu99 -g
LDFLAGS=-g
HEADERS=adder.h adderob.h bstrlib.h
all: adder
adder.o: adder.c $(HEADERS)
	$(CC) $(CFLAGS) adder.c -c -o adder.o
addergc.o: addergc.c $(HEADERS)
	$(CC) $(CFLAGS) addergc.c -c -o addergc.o
adderob.o: adderob.c $(HEADERS)
	$(CC) $(CFLAGS) adderob.c -c -o adderob.o
adderstr.o: adderstr.c $(HEADERS)
	$(CC) $(CFLAGS) adderstr.c -c -o adderstr.o
adder: adder.o addergc.o adderob.o adderstr.o
	$(CC) $(LDFLAGS) adder.o addergc.o adderob.c adderstr.o -o adder
