#ifndef MY_EXCEPTION_HEADER
#define MY_EXCEPTION_HEADER

#include <iostream>
	
class My_Exception
{
	private:
		std::string message;
		bool fatal;
	public:
		My_Exception(std::string);
		My_Exception(std::string, bool);
		My_Exception(bool, std::string);
		std::string What() const;
		bool Fatal() const;
		friend std::ostream & operator << (std::ostream & out, const My_Exception & exception);
	};

#endif
