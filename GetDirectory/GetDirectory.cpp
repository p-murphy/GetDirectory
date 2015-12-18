// GetDirectory.cpp : Defines the entry point for the console application.
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

//// CLASSES ////

class Directory
{
public:
	char directory[FILENAME_MAX];
	char *dir;
	int size = sizeof(directory);
	bool isNull = false;
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

void MoveToDirectory();

void ReadDirectory();

void PrintDirectoryDirectories();

void WriteDirectoryInformation();

std::vector<std::string> GatherDirectoryInformation();

int SetCurrentDirectory(char dir[]);

int _tmain(int argc, _TCHAR* argv[])
{
	char *workingDirectory3;
	char directoryBuffer2[FILENAME_MAX];
	char newPath[FILENAME_MAX];

	Directory *workingDirectory = new Directory();
	Directory *workingDirectory2 = new Directory();

	system("dir /ad-l");

	std::cout << "/////////////////////" << std::endl;
	std::cout << "/////////////////////" << std::endl;

	MenuSelection(workingDirectory);

	/*std::cin.ignore(32767, '\n');
	std::cin.get();*/

	return 0;
}

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
		// Return root to align with cd behavior.
		//std::cout << "currentDirectoryLength is " << currentDirectoryLength << std::endl;
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
	if (currentDirectory[currentDirectoryLength - 1] == '\\')
	{
		currentDirectory[currentDirectoryLength - 1] = '\0';
	}

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
		std::cout << "8 - Move To Directory" << std::endl;
		std::cout << "9 - End Program" << std::endl;

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
			MoveToDirectory();
			break;
		case 9:
			//std::cout << "User has selected: " << userChoice << std::endl;
			loopControl = false;
			break;
		default:
			break;
		}
	}
}

void MoveToDirectory()
{
	std::string directoryInput;
	bool exists = false;

	std::cout << "Please enter the directory you would like to move to:" << std::endl;

	// Flush buffer
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	// Gather user input
	std::getline(std::cin, directoryInput);

	std::vector<std::string> dirVect = GatherDirectoryInformation();

	std::vector<std::string>::const_iterator directoryIterator;
	directoryIterator = dirVect.begin();

	while (directoryIterator != dirVect.end())
	{
		std::cout << "comparing _" << directoryInput << "_ and _" << *directoryIterator << "_" << std::endl;

		if (directoryInput.compare(*directoryIterator) == 0)
			exists = true;

		++directoryIterator;
	}

	if (exists)
	{
		std::cout << "We found a match" << std::endl;
	}
	else
	{
		std::cout << "We did not find a match" << std::endl;
	}

	//std::cout << "You entered: " << 8 << std::endl;
	//std::cout << "Length is: " << 8 << std::endl;

}


void ReadDirectory()
{

}

void PrintDirectoryDirectories()
{
	system("dir /ad-l");
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
	std::vector<std::string> dirVect = GatherDirectoryInformation();

	std::cout << "There are " << dirVect.size() << " directories:" << std::endl;

	std::vector<std::string>::const_iterator directoryIterator;
	directoryIterator = dirVect.begin();

	while (directoryIterator != dirVect.end())
	{
		std::cout << *directoryIterator << std::endl;
		++directoryIterator;
	}
}


int SetCurrentDirectory(char dir[])
{
	if (dir == nullptr)
		return -1;

	if (_chdir(dir))
	{
		return errno;
	}

	return 0;
}