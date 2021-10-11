#include <iostream>
#include <climits>
#include "My_Exception.h"

template <typename X>
void Get_Template(X &x, std::istream & input = std::cin, std::ostream & output = std::cout) 
{
	if(typeid(X) == typeid(bool))
	{
        	output << "To input bool type use 1 or 0." << std::endl;
        }
	output << ">> ";
	while(1)
        {
                input >> x;
                if(input.eof())
                {
			throw My_Exception("EOF occured!", 1);
                }
                if(input.fail())
                {
			if(input.bad())
			{
				throw My_Exception("Problems with stream!", 1);
			}
                        output << "Wrong input! Repeat from the begining.\n>> ";
                        input.clear();
                        input.ignore(INT_MAX, '\n');
                	continue;
		}
                break;
        }
}


template <typename X, typename Y>
void Get_Template(X &x, Y &y, std::istream & input = std::cin, std::ostream & output = std::cout) 
{
	if(typeid(X) == typeid(bool) || typeid(Y) == typeid(bool))
	{
        	output << "To input bool type use 1 or 0." << std::endl;
        }
	output << ">> ";
        while(1)
        {
                input >> x >> y;
                if(input.eof())
                {
			throw My_Exception("EOF occured!", 1);
                }
                if(input.fail())
                {
			if(input.bad())
			{
				throw My_Exception("Problems with stream!", 1);
			}
                        output << "Wrong input! Repeat from the begining.\n>> ";
                        input.clear();
                        input.ignore(INT_MAX, '\n');
                        continue;
                }
                break;
        }
}

template <typename X, typename Y, typename Z>
void Get_Template(X &x, Y &y, Z &z, std::istream & input = std::cin, std::ostream & output = std::cout) 
{
	if(typeid(X) == typeid(bool) || typeid(Y) == typeid(bool) || typeid(Z) == typeid(bool))
	{
        	output << "To input bool type use 1 or 0." << std::endl;
        }
	output << ">> ";
        while(1)
        {
                input >> x >> y >> z;
                if(input.eof())
                {
			throw My_Exception("EOF occured!", 1);
                }
                if(input.fail())
                {
			if(input.bad())
			{
				throw My_Exception("Problems with stream!", 1);
			}
                        output << "Wrong input! Repeat from the begining.\n>> ";
                        output.clear();
                        input.ignore(INT_MAX, '\n');
                        continue;
                }
                break;
        }
}
