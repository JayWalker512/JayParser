#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

//defining string symbols to be parsed from text file input
#define CHAR_COMMENT ';'
#define STRING_LOOP_MARKER_SUFFIX ":"

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


#endif
