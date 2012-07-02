/*
 *  define.h
 *  JayParser
 *
 *  Created by Etienne Maheu on 10-04-17.
 *  Copyright 2010 Kawazoe Masahiro. All rights reserved.
 * 
 *  Released under MIT license on 06-01-2012 by Brandon Foltz with
 * 	permission from Etienne Maheu. Original files will retain this
 * 	copyright notice, refer to Git for changes by Brandon Foltz or other
 * 	developers.
 *
 */

////////////////////////////////////////////////////////////////////////////////
// System management
////////////////////////////////////////////////////////////////////////////////
// Registers
#define EAX 0xFFFF
#define EBX 0xFFFE
#define ECX 0xFFFD
#define EDX 0xFFFC

// Flags
#define LGF 0xFFF0	// Logical flag, hold the result of any logical operation

// Any value under 0x0010 is reserved for future upgrades

////////////////////////////////////////////////////////////////////////////////
// Sections
////////////////////////////////////////////////////////////////////////////////
#define DATASEC 0xDDFFDDFF	// Data section marker
#define CODESEC 0xCCFFCCFF	// Code section marker

////////////////////////////////////////////////////////////////////////////////
// Instruction set
////////////////////////////////////////////////////////////////////////////////

// System
// - Stuff that can't be categorised
#define NOP 0x00
#define DSP 0x01	// Display

#define MOV 0x02 // op1 = op2
#define SET 0x03 // op1 = op2

#define JMP 0x04	// Jump to ln (op)
#define JMF 0x05 // Jump if LGF is set

#define JMPMK 0x08	// Jump marker
#define RSTLG 0x09	// Reset LGF

// Arithmetic
#define ADD 0x10	// op1 += op2
#define SUB 0x11	// op1 -= op2
#define MUL 0x12 // op1 *= op2
#define DIV 0x13	// op1 /= op2
#define DEC 0x14	// --op
#define INC 0x15	// ++op

#define NEG 0x19	// -lgf

// Logical
// - Set LGF to the result of the instruction
#define EQQ 0x20	// op1 == op2
#define NEQ 0x21	// op1 != op2
#define AND 0x22	// op1 && op2
#define ORR 0x23 // op1 || op2
#define NOT 0x29 // !op

////////////////////////////////////////////////////////////////////////////////
// Errors
////////////////////////////////////////////////////////////////////////////////
#define FATAL 0x80000000
#define WARN  0x70000000
#define INFO  0x60000000

#define FILEERR 0xFFFF00
#define PARSERR 0xFFEE00
