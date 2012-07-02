/*
 *  log.h
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

#ifndef LOG_H
#define LOG_H

#include <stack>
#include <iostream>

#include "error.h"

class Log {
public:
	~Log()
	{
		while (m_errors.size()) {
			delete m_errors.top();
			m_errors.pop();
		}
	}
	
	static Log* init() {		
		if (!sm_instance)
			sm_instance = new Log();
		
		return sm_instance;
	}
	
	void displayLastError() { if (m_errors.size()) std::cerr << "Error: " << m_errors.top()->getCode() << std::endl << m_errors.top()->getText() << std::endl; }
	int getErrorCount()		{ return m_errors.size(); }
	
	void add(Error* error)	{ m_errors.push(error); }

private:
	Log() { }
	
	static Log* sm_instance;
	
	std::stack<Error*> m_errors;

};

#endif
