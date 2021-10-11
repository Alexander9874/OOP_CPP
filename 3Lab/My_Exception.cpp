#include "My_Exception.h"

My_Exception::My_Exception() : message("Some exception."), fatal(false) {}

My_Exception::My_Exception(const char * msg) : message(msg), fatal(false) {}

My_Exception::My_Exception(const char * msg, bool x) : message(msg), fatal(x) {}

My_Exception::My_Exception(bool x, const char * msg) : message(msg), fatal(x) {}

const char * My_Exception::what() const noexcept
{
	return message;
}

bool My_Exception::Fatal() const noexcept
{
	return fatal;
}

std::ostream & operator << (std::ostream & out, const My_Exception & exception)
{
	out << "Exception: \""<< exception.message << "\";\n";
	if(!exception.Fatal())
	{
		out << "not ";
	}
	out << "fatal exception.\n";
	return out;
}

#ifdef My_Exception_Main
int main()
{
	My_Exception ex("Hello", false);
	My_Exception e;
	std::cout << ex.what() << std::endl;
	std::cout << e.what() << std::endl << std::endl;

	try
	{
		throw My_Exception("Meow");
	}
	catch(std::exception exc)
	{
		std::cout << exc.what() << std::endl;
	}
}
#endif
