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

#include "../define.h"

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
		if (0 == strcmp(argv[i], "-o"))
		{
			compile_bytecode(argv[i-1], argv[i+1]);
		}
	}
}

int compile_bytecode(const char *input_file, const char *output_file)
{
	std::ifstream input_stream(input_file, std::ios::binary);
	//ifstream
	if (!input_stream.is_open())
	{
		printf("Unable to open %s\n", input_file);
		return 0;
	}	
	
	printf("Compiling bytecode from %s to %s\n", input_file, output_file);
        char in_line[256];
        unsigned int line_length = 0;
        while (input_stream.getline(in_line, 256))
        {
            line_length = strlen(in_line);
            std::cout << "LOG: Current line: " << in_line << std::endl;
            int i = 0;
            for (i=0;i<line_length;i++)
            {
                if (in_line[i] == ';')
                {
                    std::cout << "LOG: Found comment line. Skipping...\n";
                    break;
                }
                
                if (0 == strncmp((in_line+i), ".data", 5))
                    std::cout << "LOG: Matched data section.\n";
                        
            }
        }
}

