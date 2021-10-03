#include <iostream>
#include <climits>

template <typename X>
void Get_Template(X &x) 
{
        std::cout << "To expres bool type use 1 or 0.\n>> ";
        while(1)
        {
                std::cin >> x;
                if(std::cin.eof())
                {
                        throw (std::string) "EOF occured!";
                }
                if(std::cin.fail())
                {
                        std::cout << "Wrong input! Repeate from the begining.\n>> ";
                        std::cin.clear();
                }
                break;
        }
        std::cout << "Success!\n" << std::endl;
}


template <typename X, typename Y>
void Get_Template(X &x, Y &y) 
{
        std::cout << "To expres bool type use 1 or 0.\n>> ";
        while(1)
        {
                std::cin >> x;
                if(std::cin.eof())
                {
                        throw (std::string) "EOF occured!";
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
                        throw (std::string) "EOF occured!";
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
        std::cout << "Success!\n" << std::endl;
}


template <typename X, typename Y, typename Z>
void Get_Template(X &x, Y &y, Z &z) 
{
        std::cout << "To expres bool type use 1 or 0.\n>> ";
        while(1)
        {
                std::cin >> x;
                if(std::cin.eof())
                {
                        throw (std::string) "EOF occured!";
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
                        throw (std::string) "EOF occured!";
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
                        throw (std::string) "EOF occured!";
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
        std::cout << "Success!\n" << std::endl;
}
