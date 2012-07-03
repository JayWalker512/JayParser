#ifndef ASSEMBLER_H
#define ASSEMBLER_H

int compile_bytecode(const char *input_file, const char *output_file);
unsigned char byte_from_hex_str(const char *hex_string);
int bytes_from_hex_string(unsigned char *out_bytes, const char *hex_string);

#endif
