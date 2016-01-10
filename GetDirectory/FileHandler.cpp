// FileHandler.cpp :
//

#include "stdafx.h"

#include <windows.h>
#include <Shellapi.h>
#include <iostream>
#include <string>

#include "GetDirectory.h"

void Run()
{
	std::cout << "Please enter the name of the file you would like to run: " << std::endl;

	// Flush buffer
	flushBuffer();

	std::string filename;
	std::getline(std::cin, filename);

	if (ShellExecuteA(
		NULL,     // No parent window for error message boxes/...
		"open",   // Shell action ("verb") to be performed on the file (as opposed to "print", "explore", ...)
		filename.c_str(), // File to be opened
		NULL,     // Command-line parameters - not used when opening documents
		NULL,     // Working directory - the current one is used by default
		SW_SHOW   // State of the window of the application being launched - SW_SHOW is the default
		) <= (HINSTANCE)32     // If ShellExecute returns a value <=32 it means that an error has occurred
		)
	{
		std::cout << "Cannot open " << filename << " with the default editor - ShellExecute failed." << std::endl;
	}
}