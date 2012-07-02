/*
 *  VM.h
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

#ifndef VM_H
#define VM_H

#include <stack>
#include <iostream>
#include <fstream>

#include "define.h"
#include "log.h"

typedef unsigned int uint;

class VM {
public:
	VM(std::ifstream* file);
	~VM();

	void parse();
	
// Parser
private:
	void readNextSection(uint* section);
	
	void readNextInstruction();
	void skipNextInstruction();
	
	void readNextOperator(uint& op);
	inline void readNextOp1()			{ readNextOperator(m_op1); }
	inline void readNextOp2()			{ readNextOperator(m_op2); }
	inline void readNextOperators()	{ readNextOp1(); readNextOp2(); }
	
	void jumpToSection(uint section);
	
	void parseDataSection();
	void parseCodeSection();
	
// Instructions
private:
	// System
	inline void execDSP()	{ putchar(*m_edx); }
	
	inline void execMOV()	{ m_memory[m_op1] = m_memory[m_memory[m_op2]]; }
	inline void execSET()	{ m_memory[m_op1] = m_op2; }
	
	void execJMP();
	inline void execJMF() {
		if (*m_lgf != 0)
			execJMP();
		else
			skipNextInstruction();
	}
	
	inline void execJMPMK() { readNextInstruction(); }		// Skip the marker ID and continue normal execution
	inline void execRSTLG()	{ m_lgf = 0; }
	
	// Arithmetic
	inline void execADD()	{ m_memory[m_op1] += m_memory[m_op2]; }
	inline void execSUB()	{ m_memory[m_op1] -= m_memory[m_op2]; }
	inline void execMUL()	{ m_memory[m_op1] *= m_memory[m_op2]; }
	inline void execDIV()	{ m_memory[m_op1] /= m_memory[m_op2]; }
	
	inline void execDEC()	{ --m_memory[m_op1]; }
	inline void execINC()	{ ++m_memory[m_op1]; }

	
	inline void execNEG()	{ m_memory[m_op1] = 0 - m_memory[m_op1]; }
	
	// Logical
	inline void execEQQ()	{ *m_lgf = m_memory[m_op1] == m_memory[m_op2]; }
	inline void execNEQ()	{ *m_lgf = m_memory[m_op1] != m_memory[m_op2]; }
	inline void execAND()	{ *m_lgf = m_memory[m_op1] && m_memory[m_op2]; }
	inline void execORR()	{ *m_lgf = m_memory[m_op1] || m_memory[m_op2]; }
	
	inline void execNOT()	{ *m_lgf = !*m_lgf; }

private:
	// Virtual memory
	int m_memory[0xFFFF];

	int* m_eax;
	int* m_ebx;
	int* m_ecx;
	int* m_edx;
	
	uint m_ic;
	uint m_opc;
	
	uint m_instruction;
	uint m_op1;
	uint m_op2;
	
	int* m_lgf;
	
	// System
	std::ifstream* m_program;
	Log* m_log;

};

#endif
