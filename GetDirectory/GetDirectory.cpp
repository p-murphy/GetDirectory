// GetDirectory.cpp :
//

#include "stdafx.h"
#include <direct.h>
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

#include "GetDirectory.h"

void GetCurrentDirectory(Directory *dir)
{
	dir->dir = _getcwd(dir->directory, dir->size);
}

void PrintCurrentDirectory()
{
	char directoryBuffer[FILENAME_MAX];
	std::cout << _getcwd(directoryBuffer, sizeof(directoryBuffer)) << std::endl;
}

void PrintParentDirectory()
{
	char directoryBuffer[FILENAME_MAX];
	char *currentDirectory = _getcwd(directoryBuffer, sizeof(directoryBuffer));
	int currentDirectoryLength = strlen(currentDirectory);

	// Remove possible trailing backslash on path string
	cullBackslash(currentDirectory, currentDirectoryLength);

	// Isolate directory leaf at end of path
	char *finalBackslash;
	finalBackslash = strrchr(currentDirectory, '\\');

	if (finalBackslash == nullptr)
	{
		// We are at the root of the directory.
		// Return root to align with cd behavior.
		currentDirectory[currentDirectoryLength - 1] = '\\';
		currentDirectory[currentDirectoryLength] = '\0';
		std::cout << currentDirectory << std::endl; 
		return;
	}

	// Locate index of path string to be truncated
	int currentDirectoryNameLength = strlen(finalBackslash);
	int delta = currentDirectoryLength - currentDirectoryNameLength;

	// Append trailing backslash to handle root directory case
	currentDirectory[delta] = '\0';

	std::cout << currentDirectory << std::endl;
}

void PrintDirectoryObject(const Directory *dir)
{
	if (dir->dir == nullptr)
	{
		std::cout << "Error: Directory object is not initialized..." << std::endl;
		return;
	}

	if (dir->isNull == true)
	{
		std::cout << "Null directory..." << std::endl;
		return;
	}

	std::cout << dir->directory << std::endl;
}

void MoveToParentDirectory()
{
	char directoryBuffer[FILENAME_MAX];
	char* currentDirectory = _getcwd(directoryBuffer, sizeof(directoryBuffer));
	int currentDirectoryLength = strlen(currentDirectory);

	// Remove possible trailing backslash on path string
	if (currentDirectory[currentDirectoryLength - 1] == '\\')
	{
		currentDirectory[currentDirectoryLength - 1] = '\0';
	}

	// Isolate directory leaf at end of path
	char *finalBackslash;
	finalBackslash = strrchr(currentDirectory, '\\');

	if (finalBackslash == nullptr)
	{
		// We are at the root of the directory.
		// Move to root to align with cd behavior.
		_chdir(currentDirectory);

		// Print to cout
		PrintCurrentDirectory();
		return;
	}

	// Locate index of path string to be truncated
	int currentDirectoryNameLength = strlen(finalBackslash);
	int delta = currentDirectoryLength - currentDirectoryNameLength;

	// Append trailing backslash to handle root directory case
	currentDirectory[delta] = '\\';
	currentDirectory[delta + 1] = '\0';

	// Change to new directory
	_chdir(currentDirectory);

	// Print to cout
	PrintCurrentDirectory();
}

void GetParentDirectory(Directory *dir)
{
	char directoryBuffer[FILENAME_MAX];
	char *currentDirectory = _getcwd(directoryBuffer, sizeof(directoryBuffer));
	int currentDirectoryLength = strlen(currentDirectory);

	// Remove possible trailing backslash on path string
	cullBackslash(currentDirectory, currentDirectoryLength);

	// Identify directory leaf
	char *finalBackslash;
	finalBackslash = strrchr(currentDirectory, '\\');

	if (finalBackslash == nullptr)
	{
		// We are at the root of the directory.
		// Out special Null Directory.

		dir->isNull = true;
		dir->dir = "NULL\0";
		std::cout << "!Returning null directory!" << std::endl;
		return;
	}

	// Locate index of path string to be truncated
	int currentDirectoryNameLength = strlen(finalBackslash);
	int delta = currentDirectoryLength - currentDirectoryNameLength;

	// Append trailing backslash to handle root directory case
	currentDirectory[delta] = '\\';
	currentDirectory[delta + 1] = '\0';

	// Store current location to move back to after changing context to parent directory
	char tempDirectoryBuffer[FILENAME_MAX];
	char *tempDirectory = _getcwd(tempDirectoryBuffer, sizeof(tempDirectoryBuffer));

	// Change to parent directory context
	_chdir(currentDirectory);

	std::cout << "Loading this directory into parent object: " << currentDirectory << std::endl;

	// Store parent context into Directory object
	dir->dir = _getcwd(dir->directory, dir->size);

	// Return to original directory
	_chdir(tempDirectory);
}

void MenuSelection(Directory *dir)
{

	bool loopControl = true;
	int userChoice;

	while (loopControl)
	{
		std::cout << std::endl;
		std::cout << "Please choose one of the following:" << std::endl;
		std::cout << "1 - Print Current Directory Path" << std::endl;
		std::cout << "2 - Print Stored Directory Path" << std::endl;
		std::cout << "3 - Move to Parent Directory" << std::endl;
		std::cout << "4 - Load Current Directory Path into Directory Object" << std::endl;
		std::cout << "5 - Load Parent Directory Path into Directory Object" << std::endl;
		std::cout << "6 - Print Parent Directory Path" << std::endl;
		std::cout << "7 - Print Current Sub Directories" << std::endl;
		std::cout << "8 - Move To Child Directory" << std::endl;
		std::cout << "9 - Parse Absolute Directory Path" << std::endl;
		std::cout << "10 - Set Current Directory" << std::endl;
		std::cout << "11 - Print Loaded Directory Information Using Member Function" << std::endl;
		std::cout << "12 - End Program" << std::endl;

		std::cin >> userChoice;

		switch (userChoice)
		{
		case 1:
			std::cout << "User has selected: " << userChoice << std::endl;
			PrintCurrentDirectory();
			break;
		case 2:
			std::cout << "User has selected: " << userChoice << std::endl;
			PrintDirectoryObject(dir);
			break;
		case 3:
			std::cout << "User has selected: " << userChoice << std::endl;
			MoveToParentDirectory();
			break;
		case 4:
			std::cout << "User has selected: " << userChoice << std::endl;
			GetCurrentDirectory(dir);
			break;
		case 5:
			std::cout << "User has selected: " << userChoice << std::endl;
			GetParentDirectory(dir);
			break;
		case 6:
			std::cout << "User has selected: " << userChoice << std::endl;
			PrintParentDirectory();
			break;
		case 7:
			std::cout << "User has selected: " << userChoice << std::endl;
			WriteDirectoryInformation();
			break;
		case 8:
			std::cout << "User has selected: " << userChoice << std::endl;
			MoveToChildDirectory();
			break;
		case 9:
			std::cout << "User has selected: " << userChoice << std::endl;
			ParseAbsoluteDirectoryPath();
			break;
		case 10:
			std::cout << "User has selected: " << userChoice << std::endl;
			SetCurrentDirectory();
			break;
		case 11:
			std::cout << "User has selected: " << userChoice << std::endl;
			dir->PrintDirectory();
			break;
		case 12:
			//std::cout << "User has selected: " << userChoice << std::endl;
			loopControl = false;
			break;
		default:
			break;
		}
	}
}

void MoveToChildDirectory()
{
	std::string directoryInput;
	bool exists = false;

	std::cout << "Please enter the directory you would like to move to:" << std::endl;

	// Flush buffer
	flushBuffer();

	// Gather user input
	std::getline(std::cin, directoryInput);

	// If user simply pressed enter, return
	if (directoryInput.empty()){ return; }

	// Remove possible trailing backslash on path string
	cullBackslash(directoryInput);

	// Collect sub directory info
	std::vector<std::string> dirVect = GatherDirectoryInformation();

	// Verify that entire path is valid
	for (auto element : dirVect)
	{
		if (directoryInput.compare(element) == 0)
		{
			exists = true;
			break;
		}
	}

	// Move to directory if valid, if not, print error
	if (exists)
	{
		ChangeDirectory(directoryInput.c_str());
		PrintCurrentDirectory();
		return;
	}
	else
	{
		std::cout << "Directory not found..." << std::endl;
	}
}

std::vector<std::string> ParseAbsoluteDirectoryPath()
{
	/*

	Problems:
	Current logic does not handle incorrectly formatted paths.
	For now, we will assume paths are entered in the form:
	<drive>:\<directory>\<directory>\...

	Where ... is a chain of directories of arbitrary length.
	All directories are optional, but the drive is not.

	The drive can be input in any of the following formats when it is alone:
	<drive>
	<drive>:
	<drive>:\

	But when it is followed by any directory chain, it must be of the format:
	<drive>:\

	*/

	std::string path;

	std::cout << "Please enter a full directory path to parse:" << std::endl;

	// Flush buffer
	flushBuffer();

	// Gather user input
	std::getline(std::cin, path);

	// Remove possible trailing backslash on path string
	cullBackslash(path);

	std::vector<std::string> parsed;

	// If user entered only a drive
	int found = path.find_first_of(":\\");
	if (found == std::string::npos)
	{
		path += ":\\";
		std::cout << path << std::endl;
		parsed.push_back(path);
		return parsed;
	}

	// If user entered only a drive and :
	if (path[path.length() - 1] == ':')
	{
		path += "\\";
		std::cout << path << std::endl;
		parsed.push_back(path);
		return parsed;
	}

	// Leading drive edge case
	int index = path.find_first_of("\\");
	parsed.push_back(path.substr(0, index + 1));
	std::string temp = path.substr(index + 1, path.length() - index + 1);
	path = temp;
	index = path.find_first_of("\\");

	// For remaining directories, which we know that there is at least one of.
	// This loop however only works on 2 or more. See next if statement for 
	// cases with only one directory.
	while (index != std::string::npos)
	{
		parsed.push_back(path.substr(0, index));
		std::string temp = path.substr(index + 1, path.length() - index + 1);
		path = temp;
		std::cout << "Remaining path is " << path << std::endl;
		index = path.find_first_of("\\");
	}

	// Push final directory onto string vector in cases of two or more, or,
	// in cases where there is only one directory, push that directory.
	if (index == std::string::npos)
	{
		parsed.push_back(path.substr(0, index));
	}

	// Print parsed directory path to screen
	for (auto element : parsed)
	{
		std::cout << element << std::endl;
	}

	return parsed;
}

void ReadDirectory()
{

}

std::vector<std::string> GatherDirectoryInformation()
{
	char buf[FILENAME_MAX];
	FILE *pPipe;
	std::vector<std::string> dirVect;
	int length;

	// The command "dir /ad-l /b" returns only raw directory names, and nothing else at all.
	// See dir help in cmd for more information.
	if ((pPipe = _popen("dir /ad-l /b", "rt")) == NULL)
		exit(1);

	// Fill string vector with directory names
	while (fgets(buf, FILENAME_MAX, pPipe))
	{
		length = strlen(buf);
		buf[length - 1] = '\0';
		dirVect.push_back(buf);
	}
	
	/* Close pipe and print return value of pPipe. */
	if (feof(pPipe))
	{
		//std::cout << "All good." << std::endl;
	}
	else
	{
		std::cout << "Error: Failed to read the pipe to the end." << std::endl;
	}

	return dirVect;
}

void WriteDirectoryInformation()
{
	// Fill object with raw, stripped subdirectory names
	std::vector<std::string> dirVect = GatherDirectoryInformation();

	// Print to screen
	for (auto element : dirVect)
	{
		std::cout << element << std::endl;
	}
}

void SetCurrentDirectory()
{
	// Fill object with parsed list of directories in path
	std::vector<std::string> parsedDirectoryList = ParseAbsoluteDirectoryPath();

	// Save current directory location. In the case that the target path is found
	// to be invalid, we will return here.
	Directory *dir = new Directory();
	GetCurrentDirectory(dir);

	// For each parsed item, try to go to that. If we fail along the way,
	// switch back to previously saved directory, and exit the function.
	for (auto element : parsedDirectoryList)
	{
		if (ChangeDirectory(element.c_str()) != 0)
		{
			ChangeDirectory(dir->dir);
			PrintCurrentDirectory();
			return;
		}
	}

	PrintCurrentDirectory();
}

int ChangeDirectory(const char *dir)
{
	if (_chdir(dir))
	{
		switch (errno)
		{
		case ENOENT:
			std::cout << "Unable to locate the directory " << dir << "..." << std::endl;
			return errno;
		case EINVAL:
			std::cout << "Invalid buffer..." << std::endl;
			return errno;
		default:
			std::cout << "Unknown error..." << std::endl;
			return errno;
		}

		return 0;
	}
}

void flushBuffer()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void cullBackslash(std::string &path)
{
	if (path[path.length() - 1] == '\\')
	{
		std::cout << "START: " << path << std::endl;
		path.erase(path.find_last_of('\\'), std::string::npos);
		std::cout << "END: " << path << std::endl;
	}

}

void cullBackslash(char* path, int length)
{
	if (path[length - 1] == '\\')
	{
		path[length - 1] = '\0';
	}
}