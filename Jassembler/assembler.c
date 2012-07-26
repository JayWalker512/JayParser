/*
 *  assembler.c
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

#include "instructions.h"
#include "assembler.h"

extern char DEBUG;

/*TODO: Once everything works, try breaking this down into smaller functions. */
int compile_bytecode(const char *input_file, const char *output_file)
{
    //variable declarations
    FILE *input_pointer, *output_pointer;
    char output_buffer[0xFFFF] = "";
    struct t_loop_marker loop_markers[MAX_LOOP_MARKERS];
    int loop_marks = 0;
    char in_line[256] = "";
    int line_length = 0;
    int outbytes = 0;
    
    input_pointer = fopen(input_file, "r");
    output_pointer = fopen(output_file, "w");

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
    while (fgets(in_line, 255, input_pointer))
    {
		line_length = strlen(in_line);
		printf("Line length: %d\n", line_length);

		if (DEBUG)
			printf("LOG: Current line: %s\n", in_line);

		int i = 0;
		for (i=0; i<line_length; i++)
		{
			if (in_line[i] == COMMENT_PREFIX)
			{
				if (DEBUG)
					printf("LOG: Found comment line. Skipping...\n");
				break;
			}

			if (in_line[i] == LOOP_MARKER_SUFFIX)
			{	
				int loop_marker_ret = 0; //only for debugging purposes
				loop_marker_ret = add_loop_marker(loop_markers+loop_marks,
											&loop_marks, 
											in_line);

				if (DEBUG)
				{
					printf("LOG: Found loop marker\n");
					//printf("78 Length: %d\n", strlen(loop_markers[--loop_marks].string));
					if (loop_marker_ret == 1)
						printf("LOG: %s added to index.\n", loop_markers[loop_marks-1].string);
					else
						puts("Invalid marker!");

				}            	
			}

			int x = 0;
			for (x=0; x<num_instructions; x++)
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
    	
    printf("Output buffer size: %u\n", (unsigned int)strlen(output_buffer));
	
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
    for(i=0; i<len; i+=2)
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
					int *marker_count, 
					const char *marker_string)
{
    char final_loop_marker[64] = "";
    strip_loop_marker_string(final_loop_marker, marker_string);
    
    if (0 == strcmp(final_loop_marker, ".data:") ||
    	0 == strcmp(final_loop_marker, ".code:") )
    {
    	return 0;
    }
	
    //ORIGINAL LINE FOR TESTING
    strcpy(marker_index->string, final_loop_marker);
    
    ++*marker_count; /*this seems counterintuitive considering what happens on
    line 71 and 81*/
   
    return 1;
}

void strip_loop_marker_string(char *stripped_string, const char *orig_string)
{
    int colonpos, marker_start_pos = 0;
    int i = 0;

    //first, find the colon
    for (i=0; i<strlen(orig_string); i++)
    {
		if (*(orig_string+i) == ':')
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
    //(colonpos+1) because we want to include the colon and null-terminator
    strncpy(stripped_string, orig_string+marker_start_pos, (colonpos+1)-marker_start_pos);

    //append null-terminator
    //*(stripped_string+( (colonpos+1)-marker_start_pos) ) = '\0';
    printf("Stripped length: %d\n", (int)strlen(stripped_string));
}

int loop_marker_exists(struct t_loop_marker *marker_index, 
						int marker_count,
						const char *marker_string)
{
	/*puts((marker_index+0)->string);
	puts((marker_index+1)->string);*/
	
	int i = 0;
	for (i=0;i<marker_count;i++)
	{
		if (0 == strcmp((marker_index+i)->string, marker_string))
			return 1; //found a match!
	}
	return 0; //no matches!
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
