// GetDirectory.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <direct.h>
#include <iostream>
#include <string>
#include <string.h>


int GetCurrentDirectory(char dir[]);
int PrintCurrentDirectory(char dir[]);
int SetCurrentDirectory(char dir[]);

void GetParentDirectory(char parent[], char child[]);
int PrintParentDirectory(char dirParent[], char dirChild[]);

int GetUserChoice()
{
	int userChoice;
	std::cin >> userChoice;
	return userChoice;
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

	switch(userChoice)
	{
	case 0 :
		std::cout << "User has selected: " << userChoice << std::endl;
		break;
	case 1 : 
		std::cout << "User has selected: " << userChoice << std::endl;
		break;
	case 2 : 
		std::cout << "User has selected: " << userChoice << std::endl;
		break;
	case 3 : 
		std::cout << "User has selected: " << userChoice << std::endl;
		break;
	case 4 : 
		std::cout << "User has selected: " << userChoice << std::endl;
		break;
	case 5 : 
		std::cout << "User has selected: " << userChoice << std::endl;
		break;
	case 6 : 
		std::cout << "User has selected: " << userChoice << std::endl;
		break;
	}
}



int _tmain(int argc, _TCHAR* argv[])
{
	char workingDirectory[FILENAME_MAX];
	char cCurrentPath[FILENAME_MAX];
	char newPath[FILENAME_MAX];

	//MenuSelection();
	try {
		GetCurrentDirectory(cCurrentPath);
	} catch( const std::exception& e ) { // reference to the base of a polymorphic object
     std::cout << e.what(); // information from length_error printed
}
	

	GetParentDirectory(newPath, cCurrentPath);
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


	if (!_getcwd(cCurrentPath, sizeof(cCurrentPath)))
    {
		return errno;
    }

	std::cout << "Current working directory: " << cCurrentPath << std::endl;


	std::cin.ignore(32767, '\n');
    std::cin.get();

	return 0;
}

int GetCurrentDirectory(char dir[])
{
	if (!_getcwd(dir, sizeof(dir)))
    {
		std::cout << "Error in GetCurrentDirectory." << std::endl;
		return errno;
    }

    dir[sizeof(dir) - 1] = '\0';
	return 0;

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

int PrintCurrentDirectory(char dir[])
{
	if(!GetCurrentDirectory(dir))
	{
		return errno;
	}

	std::cout << dir << std::endl;

	return 0;
}

int PrintParentDirectory(char dirParent[], char dirChild[])
{
	void GetParentDirectory(char dirParent[], char dirChild[]);
	std::cout << dirParent << std::endl;

	return 0;
}