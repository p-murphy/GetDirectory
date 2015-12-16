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
void MenuSelection();

// Accept user choide for directory action
int GetUserChoice();


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

void MenuSelection()
{
	int userChoice;

	std::cout << "Please choose one of the following:" << std::endl;
	std::cout << "1 - Print Current Directory Path" << std::endl;
	std::cout << "2 - Print Current Directory Contents" << std::endl;
	std::cout << "3 - Print Parent Directory Path" << std::endl;
	std::cout << "4 - Print Parent Directory Contents" << std::endl;
	std::cout << "5 - Change to Parent Directory" << std::endl;
	std::cout << "6 - End Program" << std::endl;

	userChoice = GetUserChoice();

	switch (userChoice)
	{
	case 0:
		std::cout << "User has selected: " << userChoice << std::endl;
		break;
	case 1:
		std::cout << "User has selected: " << userChoice << std::endl;
		break;
	case 2:
		std::cout << "User has selected: " << userChoice << std::endl;
		break;
	case 3:
		std::cout << "User has selected: " << userChoice << std::endl;
		break;
	case 4:
		std::cout << "User has selected: " << userChoice << std::endl;
		break;
	case 5:
		std::cout << "User has selected: " << userChoice << std::endl;
		break;
	case 6:
		std::cout << "User has selected: " << userChoice << std::endl;
		break;
	}
}

int GetUserChoice()
{
	int userChoice;
	std::cin >> userChoice;
	return userChoice;
}