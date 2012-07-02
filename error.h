/*
 *  error.h
 *  JayParser
 *
 *  Created by Etienne Maheu on 10-04-17.
 *  Copyright 2010 Kawazoe Masahiro. All rights reserved.
 *
 * 	Released under MIT license on 06-01-2012 by Brandon Foltz with
 * 	permission from Etienne Maheu. Original files will retain this
 * 	copyright notice, refer to Git for changes by Brandon Foltz or other
 * 	developers.
 * 
 */

#ifndef ERROR_H
#define ERROR_H

#include <string>

typedef unsigned int uint;

class Error {
public:
	Error(uint code, std::string text) : m_code(code), m_text(text)	{ }
	
	uint getCode()			{ return m_code; }
	std::string getText()	{ return m_text; }
	
private:
	uint m_code;
	std::string m_text;

};

#endif
