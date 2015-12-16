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
};

//// FUNCTIONS ////

// Load current directory information into Directory object dir
void GetCurrentDirectory(Directory *dir);

// Print current directory path to cout
void PrintCurrentDirectory();

// Print path information in Directory object dir
void PrintDirectory(Directory *dir);

// Prompt user to take a directory action
void MenuSelection(Directory *dir);

// Accept user choice for directory action
int GetUserChoice();

void MoveToParentDirectory();

int SetCurrentDirectory(char dir[]);
void GetParentDirectory(char parent[], char child[]);
int PrintParentDirectory(char dirParent[], char dirChild[]);


int _tmain(int argc, _TCHAR* argv[])
{
	char *workingDirectory3;
	char directoryBuffer2[FILENAME_MAX];
	char newPath[FILENAME_MAX];

	Directory *workingDirectory = new Directory();
	Directory *workingDirectory2 = new Directory();

	GetCurrentDirectory(workingDirectory);
	PrintDirectory(workingDirectory);
	PrintCurrentDirectory();

	std::cout << "/////////////////////" << std::endl;
	std::cout << "/////////////////////" << std::endl;

	MenuSelection(workingDirectory);

	/*GetParentDirectory(newPath, directoryBuffer);
	std::cout << "GetParentDirectory: " << newPath << std::endl;
    _chdir(newPath);
    std::cout << "SYSTEM///////////////////////" << std::endl;
	system( "dir");

	GetParentDirectory(newPath, newPath);
	std::cout << "GetParentDirectory: " << newPath << std::endl;
	_chdir(newPath);
	system( "dir");

	GetParentDirectory(newPath, newPath);
	std::cout << "GetParentDirectory: " << newPath << std::endl;
	_chdir(newPath);
	system( "dir");

		GetParentDirectory(newPath, newPath);
	std::cout << "GetParentDirectory: " << newPath << std::endl;
	_chdir(newPath);
	system( "dir");

		GetParentDirectory(newPath, newPath);
	std::cout << "GetParentDirectory: " << newPath << std::endl;
	_chdir(newPath);
	system( "dir");

		GetParentDirectory(newPath, newPath);
	std::cout << "GetParentDirectory: " << newPath << std::endl;
	_chdir(newPath);
	system( "dir");

	std::cout << "" << std::endl;

	std::cout << "Current working directory: " << newPath << std::endl;

	int len = strlen(newPath);
	std::cout << "NewPath length: " << len << std::endl;

	newPath[len] = '\\';
	newPath[len + 1] = '\0';

	len = strlen("c:\\");
	std::cout << "NewPath length: " << len << std::endl;


	std::cout << "Current working directory: " << workingDirectory << std::endl;*/


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

void PrintDirectory(Directory *dir)
{
	if (dir->dir == nullptr)
	{
		std::cout << "Error: Directory object is not initialized..." << std::endl;
		return;
	}

	std::cout << _getcwd(dir->directory, dir->size) << std::endl;
}

void MoveToParentDirectory()
{
	char directoryBuffer[FILENAME_MAX];
	char* currentDirectory = _getcwd(directoryBuffer, sizeof(directoryBuffer));
	int currentDirectoryLength = strlen(currentDirectory);

	//std::cout << "Last char in currentDirectory is: " << currentDirectory[currentDirectoryLength - 1] << std::endl;

	if (currentDirectory[currentDirectoryLength - 1] == '\\')
	{
		currentDirectory[currentDirectoryLength - 1] = '\0';
	}

	char *finalBackslash;
	finalBackslash = strrchr(currentDirectory, '\\');

	if (finalBackslash == nullptr)
	{
		std::cout << "We are at the root directory. Returning..."<< std::endl;
		return;
	}

	//std::cout << "finalBackslash is: "<< finalBackslash << std::endl;
	int currentDirectoryNameLength = strlen(finalBackslash);

	int delta = currentDirectoryLength - currentDirectoryNameLength;

	//std::cout << "currentDirectoryNameLength is: " << currentDirectoryNameLength << std::endl;
	//std::cout << "currentDirectoryLength is: " << currentDirectoryLength << std::endl;
	//std::cout << "delta is: " << delta << std::endl;

	currentDirectory[delta] = '\0';

	std::cout << "Moving to parent directory: " << currentDirectory << std::endl;

	currentDirectory[delta] = '\\';
	currentDirectory[delta + 1] = '\0';
	std::cout << "Parent is: " << currentDirectory << std::endl;
	_chdir(currentDirectory);
}


void GetParentDirectory(char parent[], char child[])
{
	char *finalBackslash;
	finalBackslash = strrchr(child, '\\');
	if(finalBackslash == nullptr)
	{
		//We are at the root directory.
		//Return root, to align with cd behavior.
		std::cout << "We are at root." << std::endl;
		return;
	}
	int index = finalBackslash - child;
	std::cout << "Index is: " << index << std::endl;
	strncpy(parent, child, index);
	parent[index] = '\0';
}

void GetParentDirectory(Directory *dir)
{
	char directoryBuffer[FILENAME_MAX];
	char *finalBackslash;
	finalBackslash = strrchr(_getcwd(directoryBuffer, sizeof(directoryBuffer)), '\\');
	if (finalBackslash == nullptr)
	{
		//We are at the root directory.
		//Return root, to align with cd behavior.
		std::cout << "We are at root." << std::endl;
		return;
	}
	/*int index = finalBackslash - child;
	std::cout << "Index is: " << index << std::endl;
	strncpy(parent, child, index);
	parent[index] = '\0';*/
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
		std::cout << "4 - End Program" << std::endl;

		userChoice = GetUserChoice();

		switch (userChoice)
		{
		case 1:
			std::cout << "User has selected: " << userChoice << std::endl;
			PrintCurrentDirectory();
			break;
		case 2:
			std::cout << "User has selected: " << userChoice << std::endl;
			PrintDirectory(dir);
			break;
		case 3:
			std::cout << "User has selected: " << userChoice << std::endl;
			MoveToParentDirectory();
			break;
		case 4:
			std::cout << "User has selected: " << userChoice << std::endl;
			loopControl = false;
			break;
		case 5:
			std::cout << "User has selected: " << userChoice << std::endl;
			break;
		case 6:
			std::cout << "User has selected: " << userChoice << std::endl;
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