CC=gcc
CXX=g++
CFLAGS=-O3 -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -Wall

all: slen

slen: slen.c
	$(CC) $(CFLAGS) slen.c -lm -o slen

clean:
	rm -rf slen
