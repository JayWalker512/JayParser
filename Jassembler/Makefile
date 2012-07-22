#Makefile for Jassembler
CC = gcc
CFLAGS = -Wall

all: jasm

jasm: main.o assembler.o
	$(CC) main.o assembler.o -o jasm
	
main.o: main.c assembler.h
	$(CC) main.c -c 
	
assembler.o: assembler.c assembler.h instructions.h
	$(CC) assembler.c -c 

clean:
	rm *.o
