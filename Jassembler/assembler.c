/*
 *  assembler.cpp
 *  Jassembler
 *
 *  Created by Brandon Foltz on 07-02-2012.
 *  Copyright 2012 Brandon Foltz.
 * 
 *  See LICENSE.txt for license information.
 * 
 */

//C style includes
#include <stdio.h>
#include <string.h>

#include "instructions.h"
#include "assembler.h"

extern char DEBUG;

/* I'm sure there is a more elegant way to write this type of program, but I'm
 not particularly experienced with C++ in general, let alone string parsing
 in C++. Trying my best, can always clean it up later. */
int compile_bytecode(const char *input_file, const char *output_file)
{
	FILE *input_pointer, *output_pointer;
	input_pointer = fopen(input_file, "r");
	output_pointer = fopen(output_file, "w");
	char output_buffer[0xFFFF] = "";
	
	struct t_loop_marker loop_markers[1024];
	unsigned int loop_marks = 0;
	
	if(!output_pointer)
	{
		puts("Couldn't open output file!");
		return 1;
	}
		
	if (!input_pointer)
	{
		printf("Unable to open %s\n", input_file);
		return 0;
	}	
	
	printf("Compiling bytecode from %s to %s\n", input_file, output_file);
    char in_line[256] = "";
    unsigned int line_length = 0;
    unsigned int outbytes = 0;
    while (fgets(in_line, 255, input_pointer))
    {
        line_length = strlen(in_line);
        printf("Line length: %d\n", line_length);
        
        if (DEBUG)
        	printf("LOG: Current line: %s\n", in_line);
        
        int i = 0;
        for (i=0;i<line_length;i++)
        {
            if (in_line[i] == CHAR_COMMENT)
            {
            	if (DEBUG)
                	printf("LOG: Found comment line. Skipping...\n");
                break;
            }
            
            if (in_line[i] == STRING_LOOP_MARKER_SUFFIX)
            {
        		//validate_string(in_line, 25);
        		
        		char test_string[16] = "loop:\n\0";
        		  	
            	/*FIXME: ugh this is broken. Struct isnt passing correctly
            	or something... marker never gets written to the .string member */
             	loop_marks = add_loop_marker(loop_markers+loop_marks,
            								loop_marks, 
            								test_string);
            
            	if (DEBUG)
            	{
            		printf("LOG: Found loop marker\n");
            		printf("LOG: %s added to index.\n", loop_markers[loop_marks-1].string);
            	}            	
            }
            
            int x = 0;
            for (x=0;x<num_instructions;x++)
            {
	            if (0 == strncmp((in_line+i), 
	            	instructions[x].string, 
	            	strlen(instructions[x].string)))
	            {
	            	if (DEBUG)
	            	{
			            printf("LOG: Found instruction %s\n", instructions[x].string);			            	
			            printf("Outbytes: %d\n", (int)strlen(instructions[x].binary)); 
	                }
	                outbytes += strlen(instructions[x].binary);
	                	
	               	strncat(output_buffer,
	               			instructions[x].binary,
	               			strlen(instructions[x].binary));
	                	
	                i += strlen(instructions[x].string) - 1;
	                break;
	            }	         
            }                    
        }
	}
	//write it to the file!
    fwrite(output_buffer,
    	sizeof(char),
    	strlen(output_buffer), 
    	output_pointer);
    	
    printf("Output buffer size: %u\n", strlen(output_buffer));
	
	printf("Output %d bytes.\n", outbytes);
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

/* Adds the name of a loop marker to the loop marker index. Processes this from
marker_string after removing whitespace. Markers can only be made of 
non-whitespace characters. "Loop_Marker" is valid, "Loop	Marker" is not. */
int add_loop_marker(struct t_loop_marker *marker_index, 
					int marker_count, 
					const char *marker_string)
{
	/* Still needs to search back through the string and start at the first 
	instance of whitespace or beginning of string. */
	printf("add_loop_marker recieved: %s\n", marker_string);
	
	/*char processed_loop_marker[16] = "";
	int i = 0;
	int start_char = 0;
	
	strcpy(processed_loop_marker, marker_string);
	for (i=strlen(processed_loop_marker);i>0;i--)
	{
		if (processed_loop_marker[i] == '\n')
			processed_loop_marker[i] = '\0';
		if (processed_loop_marker[i] = ':')
			processed_loop_marker[i] = '\0';
		if (processed_loop_marker[i] == '\t' ||
			processed_loop_marker[i] == ' ')
		{
			start_char = i;
			break;
		}
	}*/
	
	//strcpy(marker_index->string, processed_loop_marker[start_char]);
	
	//ORIGINAL LINE FOR TESTING
	strcpy(marker_index->string, marker_string);
    return ++marker_count;
}

void strip_loop_marker_string(const char *stripped_string, const char *orig_string)
{
	int colonpos, marker_start_pos = 0;
	int i = 0;
	
	//first, find the colon
	for (i=0; i<strlen(orig_string); i++)
	{
		if ( *(orig_string+i) == ':' )
		{
			colonpos = i;
			break;
		}
	}
	
	//now find the first whitespace char before the loop marker text
	for (i=colonpos; i>0; i--)
	{
		if ( *(orig_string+i) == ' ' ||
			 *(orig_string+i) == '\n' ||
			 *(orig_string+i) == '\t' ||
			 *(orig_string+i) == '\r' )
		{
			marker_start_pos = i+1;
			break;
		}
	}
	
	//debug
	printf("Marker start pos: %d\n Colon pos: %d\n", marker_start_pos, colonpos);
	
	//now return it!
	strncpy(stripped_string, orig_string+marker_start_pos, colonpos-marker_start_pos);
}

void validate_string(const char *in_string, int len)
{
	int i = 0;
	for(i=0;i<len;i++)
	{
		if (*(in_string+i) == NULL)
			printf("Found NULL at %d\n", i);
		else if (*(in_string+i) == '\n')
			printf("Found newline at %d\n", i);
	}
}
