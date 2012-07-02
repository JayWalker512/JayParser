#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

//defining string symbols to be parsed from text file input

struct t_instruction {
	const char instruction_str[16];
	const char instruction_binary[16];
};

t_instruction instructions[] = {
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
#define STRING_LOOP_MARKER_SUFFIX ":"

/*
#define STRING_EAX "EAX"
#define STRING_EBX "EBX"
#define STRING_ECX "ECX"
#define STRING_EDX "EDX"

#define STRING_LFG "LGF"

#define STRING_DATASEC ".data"
#define STRING_CODESEC ".code"

#define STRING_ADD "ADD"
#define STRING_SUB "SUB"

//define binary output symbols
#define BINARY_DATASEC "\xDD\xFF\xDD\xFF"
#define BINARY_CODESEC "\xCC\xFF\xCC\xFF"

#define BINARY_NOP "\x00"
#define BINARY_DSP "\x01"

#define BINARY_MOV "\x02"
#define BINARY_SET "\x03"

#define BINARY_JMP "\x04"
#define BINARY_JMF "\x05"

#define BINARY_JMPMK "\x08"
#define BINARY_RSTLG "\x09"
*/

#endif
