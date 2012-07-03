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

struct t_loop_marker {
	char string[16];
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
int add_loop_marker(t_loop_marker *marker_index, 
					int marker_count, 
					const char *marker_string);

#endif
