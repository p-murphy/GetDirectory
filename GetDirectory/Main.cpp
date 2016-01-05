// Main.cpp : Defines the entry point for the console application.
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
#include "FileHandler.h"

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