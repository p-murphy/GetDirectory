// GetDirectory.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <direct.h>
#include <iostream>
#include <string>
#include <string.h>


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

// Load current directory information into Directory object dir
void GetCurrentDirectory(Directory *dir);

// Print current directory path to cout
void PrintCurrentDirectory();

// Print path information in Directory object dir
void PrintDirectoryObject(Directory *dir);

// Prompt user to take a directory action
void MenuSelection(Directory *dir);

// Accept user choice for directory action
int GetUserChoice();

// Change context to containing directory
void MoveToParentDirectory();

int SetCurrentDirectory(char dir[]);
void GetParentDirectory(Directory *dir);
int PrintParentDirectory(char dirParent[], char dirChild[]);


int _tmain(int argc, _TCHAR* argv[])
{
	char *workingDirectory3;
	char directoryBuffer2[FILENAME_MAX];
	char newPath[FILENAME_MAX];

	Directory *workingDirectory = new Directory();
	Directory *workingDirectory2 = new Directory();

<<<<<<< HEAD
=======
	//GetCurrentDirectory(workingDirectory);
	//PrintDirectoryObject(workingDirectory);
	//PrintCurrentDirectory();

>>>>>>> 0051405ddfbd7a2adbf98f5bc29f2f7e8a87cf7f
	std::cout << "/////////////////////" << std::endl;
	std::cout << "/////////////////////" << std::endl;

	MenuSelection(workingDirectory);

	std::cin.ignore(32767, '\n');
    std::cin.get();

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

void PrintDirectoryObject(Directory *dir)
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

	// Identify directory leaf
	char *finalBackslash;
	finalBackslash = strrchr(currentDirectory, '\\');

	if (finalBackslash == nullptr)
	{
		// We are at the root of the directory.
		_chdir(currentDirectory);
		return;
	}

	// Locate index of path string to be truncated
	int currentDirectoryNameLength = strlen(finalBackslash);
	int delta = currentDirectoryLength - currentDirectoryNameLength;

<<<<<<< HEAD
	// Null terminate string, print to screen
=======
	// Print to screen
>>>>>>> 0051405ddfbd7a2adbf98f5bc29f2f7e8a87cf7f
	currentDirectory[delta] = '\0';
	std::cout << "Moving to parent directory: " << currentDirectory << std::endl;

	// Append trailing backslash to handle root directory case
	currentDirectory[delta] = '\\';
	currentDirectory[delta + 1] = '\0';

<<<<<<< HEAD
=======
	std::cout << "Moving to this parent directory: " << currentDirectory << std::endl;

>>>>>>> 0051405ddfbd7a2adbf98f5bc29f2f7e8a87cf7f
	// Change to new directory
	_chdir(currentDirectory);
}


void GetParentDirectory(Directory *dir)
{
	char directoryBuffer[FILENAME_MAX];
<<<<<<< HEAD
	char *currentDirectory = _getcwd(directoryBuffer, sizeof(directoryBuffer));
	int currentDirectoryLength = strlen(currentDirectory);

=======
	char tempDirectoryBuffer[FILENAME_MAX];
	char *currentDirectory = _getcwd(directoryBuffer, sizeof(directoryBuffer));
	int currentDirectoryLength = strlen(currentDirectory);

	std::cout << "GPD#1: " << currentDirectory << std::endl;

>>>>>>> 0051405ddfbd7a2adbf98f5bc29f2f7e8a87cf7f
	// Remove possible trailing backslash on path string
	if (currentDirectory[currentDirectoryLength - 1] == '\\')
	{
		currentDirectory[currentDirectoryLength - 1] = '\0';
	}

<<<<<<< HEAD
=======
	std::cout << "GPD#2: " << currentDirectory << std::endl;

>>>>>>> 0051405ddfbd7a2adbf98f5bc29f2f7e8a87cf7f
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

<<<<<<< HEAD
=======
	std::cout << "GPD#3: " << currentDirectory << std::endl;

>>>>>>> 0051405ddfbd7a2adbf98f5bc29f2f7e8a87cf7f
	// Locate index of path string to be truncated
	int currentDirectoryNameLength = strlen(finalBackslash);
	int delta = currentDirectoryLength - currentDirectoryNameLength;

	// Append trailing backslash to handle root directory case
	currentDirectory[delta] = '\0';
	currentDirectory[delta] = '\\';
	currentDirectory[delta + 1] = '\0';

<<<<<<< HEAD
	// Store current location to move back to after changing context to parent directory
	char tempDirectoryBuffer[FILENAME_MAX];
	char *tempDirectory = _getcwd(tempDirectoryBuffer, sizeof(tempDirectoryBuffer));

	// Change to parent directory context
	_chdir(currentDirectory);

=======
	std::cout << "GPD#4: " << currentDirectory << std::endl;

	// Store current location to move back to after changing context to parent directory
	char *tempDirectory = _getcwd(tempDirectoryBuffer, sizeof(tempDirectoryBuffer));

	std::cout << "GPD#5: " << currentDirectory << std::endl;

	// Change to parent directory context
	_chdir(currentDirectory);

	std::cout << "GPD#6: " << currentDirectory << std::endl;
>>>>>>> 0051405ddfbd7a2adbf98f5bc29f2f7e8a87cf7f
	std::cout << "Loading this directory into parent object: " << currentDirectory << std::endl;

	// Store parent context into Directory object
	dir->dir = _getcwd(dir->directory, dir->size);

	// Return to original directory
	_chdir(tempDirectory);
}

int SetCurrentDirectory(char dir[])
{
	if(dir == nullptr)
		return -1;

	if (_chdir(dir))
    {
		return errno;
    }

	return 0;
}

int PrintParentDirectory(char dirParent[], char dirChild[])
{
	void GetParentDirectory(char dirParent[], char dirChild[]);
	std::cout << dirParent << std::endl;

	return 0;
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
		std::cout << "6 - End Program" << std::endl;

		userChoice = GetUserChoice();

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
			loopControl = false;
			break;
		default:
			break;
		}
	}
}

int GetUserChoice()
{
	int userChoice;
	std::cin >> userChoice;
	return userChoice;
}