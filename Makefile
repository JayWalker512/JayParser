#Makefile for JayParser
CC = g++
CFLAGS = -Wall

all: jayvm

jayvm: main.o VM.o log.o error.o
	$(CC) main.o VM.o log.o error.o -o jayvm
	
main.o: main.cpp VM.h
	$(CC) main.cpp -c 
	
VM.o: VM.cpp VM.h
	$(CC) VM.cpp -c 
	
log.o: log.cpp log.h
	$(CC) log.cpp -c 
	
error.o: error.cpp error.h
	$(CC) error.cpp -c 
	
clean:
	rm *.o
