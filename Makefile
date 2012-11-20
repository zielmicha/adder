CC=gcc
CFLAGS=-Wall -Werror -pedantic -std=gnu99 -g
LDFLAGS=-g
HEADERS=adder.h adderob.h
all: adder
adder.o: adder.c $(HEADERS)
	$(CC) $(CFLAGS) adder.c -c -o adder.o
addergc.o: addergc.c $(HEADERS)
	$(CC) $(CFLAGS) addergc.c -c -o addergc.o
adderob.o: adderob.c $(HEADERS)
	$(CC) $(CFLAGS) adderob.c -c -o adderob.o
adderstr.o: adderstr.c $(HEADERS)
	$(CC) $(CFLAGS) adderstr.c -c -o adderstr.o
addercore.o: addercore.c $(HEADERS)
	$(CC) $(CFLAGS) addercore.c -c -o addercore.o
adderdict.o: adderdict.c $(HEADERS)
	$(CC) $(CFLAGS) adderdict.c -c -o adderdict.o
adder: adder.o addergc.o adderob.o adderstr.o addercore.o adderdict.ol
	$(CC) $(LDFLAGS) adder.o addergc.o adderob.c adderstr.o addercore.o adderdict.o -o adder
