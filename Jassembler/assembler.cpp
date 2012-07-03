#include <iostream>
#include <fstream>

//C style includes
#include <string.h>
#include <stdio.h>

#include "instructions.h"
#include "assembler.h"

struct t_loop_marker {
	char string[16];
};

t_loop_marker loop_markers[0xFFFF];
unsigned int loop_marks = 0;
extern char DEBUG;

/* I'm sure there is a more elegant way to write this type of program, but I'm
 not particularly experienced with C++ in general, let alone string parsing
 in C++. Trying my best, can always clean it up later. */
int compile_bytecode(const char *input_file, const char *output_file)
{
	std::ifstream input_stream(input_file, std::ios::binary);
	std::ofstream output_stream;
	output_stream.open(output_file, std::ios::out | std::ios::binary);
	if (output_stream.is_open())
		;
	else
	{
		puts("Couldn't open output file!");
		return 1;
	}
		
	//ifstream
	if (!input_stream.is_open())
	{
		printf("Unable to open %s\n", input_file);
		return 0;
	}	
	
	printf("Compiling bytecode from %s to %s\n", input_file, output_file);
    char in_line[256];
    unsigned int line_length = 0;
    unsigned int outbytes = 0;
    while (input_stream.getline(in_line, 256))
    {
        line_length = strlen(in_line);
        
        if (DEBUG)
        	std::cout << "LOG: Current line: " << in_line << std::endl;
        
        int i = 0;
        for (i=0;i<line_length;i++)
        {
            if (in_line[i] == CHAR_COMMENT)
            {
            	if (DEBUG)
                	std::cout << "LOG: Found comment line. Skipping...\n";
                break;
            }
            
            if (in_line[i] == STRING_LOOP_MARKER_SUFFIX)
            {
            	/*TODO: this should be encapsulated in a function of its own
            	should also not add whitespace at beginning of line. 
            	marker name only please.*/
            	strncpy(loop_markers[loop_marks].string, in_line, i);
            	loop_marks++;
            
            	if (DEBUG)
            	{
            		std::cout << "LOG: Found loop marker" << std::endl;
            		std::cout << "LOG: " << loop_markers[loop_marks-1].string << " added to index." << std::endl;
            	}            	
            }
            
            int x = 0;
            for (x=0;x<num_instructions;x++)
            {
	            if (0 == strncmp((in_line+i), 
	            	instructions[x].instruction_str, 
	            	strlen(instructions[x].instruction_str)))
	            {
	            	if (DEBUG)
	            	{
			            std::cout << "LOG: Found instruction " \
			            	<< instructions[x].instruction_str << std::endl;
			            	
			            std::cout << "Outbytes: " << strlen(instructions[x].instruction_binary)  << std::endl;
	                }
	                outbytes += strlen(instructions[x].instruction_binary);
	                
	                //just a test:
	                output_stream.write(instructions[x].instruction_binary, 
	                	strlen(instructions[x].instruction_binary) );
	                	
	                i += strlen(instructions[x].instruction_str) - 1;
	                break;
	            }	         
            }                    
        }
	}
	std::cout << "Output " << outbytes << " bytes." << std::endl;
	return 0;
}

/* Returns a byte of value equal to that represented by a 2 character hex
string. Ex. input of "A4" returns 164. */
unsigned char byte_from_hex_str(const char *hex_string)
{
	unsigned char outbyte = 0;
	unsigned char value1, value2 = 0;
	puts(hex_string);
	
	if (hex_string[0] >= 48 && hex_string[0] <= 57)
		value1 = hex_string[0] - 48;
	else if (hex_string[0] >= 65 && hex_string[0] <= 70)
		value1 = hex_string[0] - 55;
		
	if (hex_string[1] >= 48 && hex_string[1] <= 57)
		value2 = hex_string[1] - 48;
	else if (hex_string[1] >= 65 && hex_string[1] <= 70)
		value2 = hex_string[1] - 55;
		
	printf("Val1: %d, Val2: %d\n", value1, value2);
	
	outbyte = value1;
	outbyte = outbyte << 4;
	outbyte = outbyte + value2;
	printf("Outbyte: %d\n", outbyte);
	return outbyte;
}

/* Writes a string of bytes to out_bytes converted from the hex values in 
hex_string. hex_string must be a length divisible by 2. Returns value 0 if 
completed successfully, 1 on error. */
int bytes_from_hex_string(unsigned char *out_bytes, const char *hex_string)
{
	if (0 != strlen(hex_string) % 2)
		return 1; //not divisible by 2!
		
	int i = 0;
	int outbyte_counter = 0;
	int len = strlen(hex_string);
	for(i=0;i<len;i+=2)
	{
		char hex_string_piece[2] = "";
		hex_string_piece[0] = *(hex_string+i);
		hex_string_piece[1] = *(hex_string+(i+1));
		*(out_bytes+outbyte_counter) = byte_from_hex_str(hex_string_piece);
		outbyte_counter++;
	}
	return 0;
}
