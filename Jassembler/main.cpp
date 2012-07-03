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

#include <stdio.h>
#include <string.h>

#include "assembler.h"

#define HELP_TEXT "Usage: jasm [flags] [IN_FILE] [operation flag] [OUT_FILE]\n\n" \
				" flags:\n" \
				" -d	debug mode \n" \
				" --help	prints this help text\n\n" \
				" operation flags: \n" \
				" -o	output binary bytecode file\n" \

char DEBUG = 0;

int parse_args(int argc, const char *argv[]);

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

