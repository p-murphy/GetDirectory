// FileHandler.cpp :
//

#include "stdafx.h"

#include <windows.h>
#include <Shellapi.h>


void Run()
{
	if (ShellExecute(
		NULL,     // No parent window for error message boxes/...
		TEXT("open"),   // Shell action ("verb") to be performed on the file (as opposed to "print", "explore", ...)
		TEXT("testtest.txt"), // File to be opened
		NULL,     // Command-line parameters - not used when opening documents
		NULL,     // Working directory - the current one is used by default
		SW_SHOW   // State of the window of the application being launched - SW_SHOW is the default
		) <= (HINSTANCE)32     // If ShellExecute returns a value <=32 it means that an error has occurred
		)
	{
		puts("Cannot open testtest.txt with the default editor - ShellExecute failed.");
	}
}