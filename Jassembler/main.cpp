/*
 *  main.cpp
 *  Jassembler
 *
 *  Created by Brandon Foltz on 07-02-2012.
 *  Copyright 2012 Brandon Foltz.
 * 
 *  See LICENSE.txt for license information.
 * 
 */

#include <iostream>
#include <fstream>
#include <string.h>

#include "instructions.h"

#define HELP_TEXT "Usage: jasm [flags] [IN_FILE] [operation flag] [OUT_FILE]\n\n" \
				" flags:\n" \
				" -d	debug mode \n" \
				" --help	prints this help text\n\n" \
				" operation flags: \n" \
				" -o	output binary bytecode file\n" \

char DEBUG = 0;

int parse_args(int argc, const char *argv[]);
int compile_bytecode(const char *input_file, const char *output_file);

int main(int argc, const char *argv[])
{
	parse_args(argc, argv);
	return 0;
}

int parse_args(int argc, const char *argv[])
{
	int i = 0;
	for(i = 0;i<argc;i++)
	{
		//puts(argv[i]);
		if (0 == strcmp(argv[i], "--help"))
		{
			puts(HELP_TEXT);
		}
		
		if (0 == strcmp(argv[i], "-d"))
		{
			DEBUG = 1;
		}
		
		if (0 == strcmp(argv[i], "-o"))
		{
			return compile_bytecode(argv[i-1], argv[i+1]);
		}
	}
}

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

