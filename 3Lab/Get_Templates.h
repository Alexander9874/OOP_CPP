#include <iostream>
#include <climits>
#include "My_Exception.h"

template <typename X>
void Get_Template(X &x) 
{
	if(typeid(X) == typeid(bool))
	{
        	std::cout << "To express bool type use 1 or 0." << std::endl;
        }
	std::cout << ">> ";
	while(1)
        {
                std::cin >> x;
                if(std::cin.eof())
                {
			throw My_Exception("EOF occured!", 1);
                }
                if(std::cin.fail())
                {
                        std::cout << "Wrong input! Repeate from the begining.\n>> ";
                        std::cin.clear();
                        std::cin.ignore(INT_MAX, '\n');
                	continue;
		}
                break;
        }
}


template <typename X, typename Y>
void Get_Template(X &x, Y &y) 
{
	if(typeid(X) == typeid(bool) || typeid(Y) == typeid(bool))
	{
        	std::cout << "To express bool type use 1 or 0." << std::endl;
        }
	std::cout << ">> ";
        while(1)
        {
                std::cin >> x;
                if(std::cin.eof())
                {
			throw My_Exception("EOF occured!", 1);
                }
                if(std::cin.fail())
                {
                        std::cout << "Wrong input! Repeate from the begining.\n>> ";
                        std::cin.clear();
                        std::cin.ignore(INT_MAX, '\n');
                        continue;
                }
                std::cin >> y;
                if(std::cin.eof())
                {
			throw My_Exception("EOF occured!", 1);
                }
                if(std::cin.fail())
                {
                        std::cout << "Wrong input! Repeate from the begining.\n>> ";
                        std::cin.clear();
                        std::cin.ignore(INT_MAX, '\n');
                        continue;
                }
                break;
        }
}

template <typename X, typename Y, typename Z>
void Get_Template(X &x, Y &y, Z &z) 
{
	if(typeid(X) == typeid(bool) || typeid(Y) == typeid(bool) || typeid(Z) == typeid(bool))
	{
        	std::cout << "To express bool type use 1 or 0." << std::endl;
        }
	std::cout << ">> ";
        while(1)
        {
                std::cin >> x;
                if(std::cin.eof())
                {
			throw My_Exception("EOF occured!", 1);
                }
                if(std::cin.fail())
                {
                        std::cout << "Wrong input! Repeate from the begining.\n>> ";
                        std::cin.clear();
                        std::cin.ignore(INT_MAX, '\n');
                        continue;
                }
                std::cin >> y;
                if(std::cin.eof())
                {
			throw My_Exception("EOF occured!", 1);
                }
                if(std::cin.fail())
                {
                        std::cout << "Wrong input! Repeate from the begining.\n>> ";
                        std::cin.clear();
                        std::cin.ignore(INT_MAX, '\n');
                        continue;
                }
                std::cin >> z;
                if(std::cin.eof())
                {
			throw My_Exception("EOF occured!", 1);
                }
                if(std::cin.fail())
                {
                        std::cout << "Wrong input! Repeate from the begining.\n>> ";
                        std::cin.clear();
                        std::cin.ignore(INT_MAX, '\n');
                        continue;
                }
                break;
        }
}
