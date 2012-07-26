/*
 *  assembler.h
 *  Jassembler
 *
 *  Created by Brandon Foltz on 07-02-2012.
 *  Copyright 2012 Brandon Foltz.
 * 
 *  See LICENSE.txt for license information.
 * 
 */

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#define MAX_LOOP_MARKER_STRING_LENGTH 64
#define MAX_LOOP_MARKERS 4096

struct t_loop_marker {
	char string[MAX_LOOP_MARKER_STRING_LENGTH];
};

int compile_bytecode(const char *input_file, const char *output_file);

/* Returns a byte of value equal to that represented by a 2 character hex
string. Ex. input of "A4" returns 164. */
unsigned char byte_from_hex_str(const char *hex_string);

/* Writes a string of bytes to out_bytes converted from the hex values in 
hex_string. hex_string must be a length divisible by 2. Returns value 0 if 
completed successfully, 1 on error. */
int bytes_from_hex_string(unsigned char *out_bytes, const char *hex_string);

/* Adds the name of a loop marker to the loop marker index. Processes this from
marker_string after removing whitespace. Markers can only be made of 
non-whitespace characters. "Loop_Marker" is valid, "Loop	Marker" is not. */
int add_loop_marker(struct t_loop_marker *marker_index, 
					int *marker_count, 
					const char *marker_string);
					
/* Strips whitespace and newline characters from after the loop-marker ":" 
character, and strips characters to the left of the last whitespace character
before the loop marker (since loop markers cannot contain whitespace). So for 
example orig_string contains "   bla nope thisloop:   " then stripped_string
will return "thisloop". */
void strip_loop_marker_string(char *stripped_string, const char *orig_string);

/* Checks if a particular loop marker string already exists within the index.
 Returns 1 if yes, 0 if no. */
int loop_marker_exists(struct t_loop_marker *marker_index, 
						int marker_count,
						const char *marker_string);
					
/* Prints some debug info about the given string. Length, how many (and where)
null bytes and newlines are. */
void validate_string(const char *in_string, int len);

#endif
