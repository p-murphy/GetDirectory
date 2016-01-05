#ifndef GET_DIRECTORY
#define GET_DIRECTORY


#include "stdafx.h"
#include <direct.h>
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

//// CLASSES ////

class Directory
{
public:
	char directory[FILENAME_MAX];
	char *dir;
	int size = sizeof(directory);
	bool isNull = false;

	char* GetDirectory() { return dir; }

	void PrintDirectory()
	{
		if (dir == nullptr)
		{
			std::cout << "Error: Directory object is not initialized..." << std::endl;
			return;
		}

		if (isNull == true)
		{
			std::cout << "Null directory..." << std::endl;
			return;
		}

		std::cout << directory << std::endl;
	}

	void StoreCurrentDirectory()
	{
		dir = _getcwd(directory, size);
	}
};

//// FUNCTIONS ////

/*
Directory functions are designated by being 1 of 2 types. Type 1 perform
actions without needing a reference to an existing Directory objects. These
actions are generally concerned with current user directory context, such as printing
and changing context.

Type 2 require a reference to an existing Directory object. These actions
will generally act on storing or retrieving a directory context.

*/

// Print current directory path to cout
void PrintCurrentDirectory();

// Print path of current containing directory to cout
void PrintParentDirectory();

// Change context to containing directory
void MoveToParentDirectory();

// Load current directory information into Directory object dir
void GetCurrentDirectory(Directory *dir);

// Print path information in Directory object dir
void PrintDirectoryObject(const Directory *dir);

// Load parent directory information into Directory object
// Load special Null Directory if we are at the root
void GetParentDirectory(Directory *dir);

// Prompt user to take a directory action
void MenuSelection(Directory *dir);

// Change directory context to arbitrary location
void MoveToChildDirectory();

// Not implimented yet
void ReadDirectory();

// Like PrintDirectoryDirectories, but writes only raw Directory names, and nothing else at all
void WriteDirectoryInformation();

// Takes an arbitrary string of path information and parses and prints each to screen as a separate line
// *To be changed later*
std::vector<std::string> ParseAbsoluteDirectoryPath();

// Not implemented yet
void SetCurrentDirectory();

// Support function which changes current directory context
int ChangeDirectory(const char *dir);

// Support function for functions which need raw directory names
std::vector<std::string> GatherDirectoryInformation();

// Support function to flush buffer
void flushBuffer();

// Clears trailing backslashes from std::strings
void cullBackslash(std::string &path);

// Clears trailing backslashes from c_strings
void cullBackslash(char* path, int length);

#endif