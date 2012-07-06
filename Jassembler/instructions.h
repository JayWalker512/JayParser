/*
 *  instructions.h
 *  Jassembler
 *
 *  Created by Brandon Foltz on 07-02-2012.
 *  Copyright 2012 Brandon Foltz.
 * 
 *  See LICENSE.txt for license information.
 * 
 */

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

struct t_instruction {
	const char string[16];
	const char binary[16];
};

//defining string symbols to be parsed from text file input
struct t_instruction instructions[] = {
	".data", "\xDD\xFF\xDD\xFF",
	".code", "\xCC\xFF\xCC\xFF",
	"EAX", "\xFF\xFF",
	"EBX", "\xFF\xFE",
	"ECX", "\xFF\xFD",
	"EDX", "\xFF\xFC",
	"LGF", "\xFF\xF0",
	"NOP", "\x00",
	"DSP", "\x01",
	"MOV", "\x02",
	"SET", "\x03",
	"JMP", "\x04",
	"JMF", "\x05",
	"JMPMK", "\x08",
	"RSTLG", "\x09",
	"ADD", "\x10",
	"SUB", "\x11",
	"MUL", "\x12",
	"DIV", "\x13",
	"DEC", "\x14",
	"INC", "\x15",
	"NEG", "\x19",
	"EQQ", "\x20",
	"NEQ", "\x21",
	"AND", "\x22",
	"ORR", "\x23",
	"NOT", "\x29"
	};
	
int num_instructions = 27;

#define CHAR_COMMENT ';'
#define STRING_LOOP_MARKER_SUFFIX ':'

#endif
