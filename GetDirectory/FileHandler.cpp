// FileHandler.cpp :
//

#include "stdafx.h"

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#include <Shellapi.h>


void Run()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	//if (argc != 2)
	//{
	//	printf("Usage: %s [cmdline]\n", argv[0]);
	//	return;
	//}

	// Start the child process. 
	if (!CreateProcess(TEXT("C:\\Windows\\notepad.exe"),   // No module name (use command line)
		TEXT("testtest.txt"),        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return;
	}

	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void Run2()
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