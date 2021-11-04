#ifndef MENU_NOT_MINE
#define MENU_NOT_MINE

#pragma once

#include <limits> 

#include "table.h" 

const char *FUNCS[] = {"0. Quit",
					   "1. Add element",
                       "2. Find element",
                       "3. Find information",
                       "4. Delete element",
                       "5. Print table",
                   	   "6. Refresh table"};


template <typename T>
input input_type(const char *msg, T &res)
{
	std::cout << msg << std::endl;
	std::cin >> res;
	if (std::cin.bad()) { return CRASH; }
	if (std::cin.eof()) { return END_OF_FILE; }
	if (std::cin.fail()) { 
		std::cin.clear(); 
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return INVALID;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return GOOD;
}

template <typename T> input input_type(const char *, int &);
template <typename T> input input_type(const char *, Item &);

const int FUNCS_SIZE = sizeof(FUNCS) / sizeof(FUNCS[0]);


void menu();

int dialog(const char *funcs[], int n);



#endif