#ifndef EXCEPTIONS_HEADER
#define EXCEPTIONS_HEADER

#include <exception>
//#include <stdexcept>

class Exception : public std::exception
{
	private:
		const char * message;
	public:
		Exception() : message("Some exception.") {};
		Exception(const char * msg) : message(msg) {};
		virtual const char* what() const noexcept
        {
            return message;
        }
};

class Game_Over : public std::exception
{
	public:
	virtual const char * what() const noexcept
	{
		return "Game_Over";
	}
};

#endif