/*
 *  VM.cpp
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

#include "VM.h"

VM::VM(std::ifstream *file) : m_ic(0), m_opc(0), m_op1(0), m_op2(0), m_program(file)
{
	m_log = Log::init();
	
	for (uint i = 0; i < 0xFFFF; ++i)
		m_memory[i] = 0;
	
	m_eax = m_memory + EAX;
	m_ebx = m_memory + EBX;
	m_ecx = m_memory + ECX;
	m_edx = m_memory + EDX;
	
	m_lgf = m_memory + LGF;
}
VM::~VM()
{
	
}

void VM::parse()
{
	parseDataSection();
	
	if (m_log->getErrorCount())
		return;

	parseCodeSection();
}

// Parser
////////////////////////////////////////////////////////////////////////////////
void VM::readNextSection(uint *section)
{
	char block;
	m_program->get(block);
	*section = (*section << 8) + (unsigned char)block;
}

void VM::readNextInstruction()
{
	char buffer;
	m_program->get(buffer);
	
	m_instruction = (unsigned char)buffer;	
	++m_ic;
	
	switch (m_instruction) {
		case NOP:
		case DSP:
		case RSTLG:
		case JMP:
		case JMF:
		case JMPMK:
		case NOT:
			return;
		case DEC:
		case INC:
		case NEG:
			readNextOp1();
			return;
		case MOV:
		case SET:
		case ADD:
		case SUB:
		case MUL:
		case DIV:
		case EQQ:
		case NEQ:
		case AND:
		case ORR:
			readNextOperators();
			return;
	}
}

void VM::skipNextInstruction()
{
	m_program->seekg(1, std::ios_base::cur);
}

void VM::readNextOperator(uint& op)
{
	char high, low;
	m_program->get(high);
	m_program->get(low);
	
	op = ((unsigned char)high << 8) + (unsigned char)low;
	
	++m_opc;
}

void VM::jumpToSection(uint section)
{
	uint buffer = 0;
	
	m_program->seekg(0, std::ios_base::beg);
	
	// Fill the buffer
	readNextSection(&buffer);
	readNextSection(&buffer);
	readNextSection(&buffer);
	
	do {
		readNextSection(&buffer);
		if (buffer == section)
			return;
	} while (!m_program->eof());
	
	m_log->add(new Error(FATAL + PARSERR + 4, "Cannot find requested section."));
}

void VM::parseDataSection()
{	
	jumpToSection(DATASEC);
	
	// Parse
	while (!m_program->eof()) {
		readNextOperators();
		
		if ((uint)((m_op1 << 16) + m_op2) == CODESEC)
			return;
		
		for (uint i = 0; i < m_op1; ++i) {
			m_memory[m_op2 + i] = m_program->get();
		}
	}
	
	m_log->add(new Error(FATAL + PARSERR + 5, "Infinite data section."));
}
void VM::parseCodeSection()
{	
	jumpToSection(CODESEC);
	
	// Parse
	while (!m_program->eof()) {
		readNextInstruction();
		
		switch (m_instruction)
		{
			case NOP:
				break;
			case DSP:
				execDSP();
				break;
			case MOV:
				execMOV();
				break;
			case SET:
				execSET();
				break;
			case JMP:
				execJMP();
				break;
			case JMF:
				execJMF();
				break;
			case JMPMK:
				execJMF();
				break;
			case RSTLG:
				execRSTLG();
				break;		
			case ADD:
				execADD();
				break;
			case SUB:
				execSUB();
				break;
			case MUL:
				execMUL();
				break;
			case DIV:
				execDIV();
				break;
			case DEC:
				execDEC();
				break;
			case INC:
				execINC();
				break;
			case NEG:
				execNEG();
				break;
			case EQQ:
				execEQQ();
				break;
			case NEQ:
				execNEQ();
				break;
			case AND:
				execAND();
				break;
			case ORR:
				execORR();
				break;
			case NOT:
				execNOT();
				break;
			default:
				m_log->add(new Error(FATAL + PARSERR + 1, "Unknown instruction."));
		}
						   
		if (m_log->getErrorCount())
			return;
	}
}

// Instructions
////////////////////////////////////////////////////////////////////////////////
void VM::execJMP()
{
	readNextInstruction();	// Using instruction as buffer for the ID
	
	m_program->seekg(0, std::ios_base::beg);
	
	do {
		if ((unsigned char)m_program->get() == JMPMK)
			if ((unsigned char)m_program->get() == m_instruction)
				return;	// Marker is found
	} while (!m_program->eof());
	
	m_log->add(new Error(FATAL + FILEERR + 3, "Trying to read pass the end of file."));
	m_log->add(new Error(FATAL + PARSERR + 2, "Jump marker not found."));
}
