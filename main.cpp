/*
 *  main.cpp
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

#include "VM.h"

int main (int argc, const char *argv[])
{
	Log *log = Log::init();
	
	if (argc != 2)
		log->add(new Error(FATAL + FILEERR + 1, "Invalid argument count. Expecting program file name."));
	else
	{
		std::ifstream inputFile(argv[1], std::ios::binary);
		
		if (!inputFile.is_open())
			log->add(new Error(FATAL + FILEERR + 2, "Can't open the file."));
		else
		{
			// Everything's looking good, starting the VM
			VM vm(&inputFile);
			vm.parse();
		}
	}
	
	Log::init()->displayLastError();
	
	return 0;
}
