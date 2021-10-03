#include "My_Exception.h"

My_Exception::My_Exception(std::string msg) : message(msg), fatal(false) {}

My_Exception::My_Exception(std::string msg, bool x) : message(msg), fatal(x) {}

My_Exception::My_Exception(bool x, std::string msg) : message(msg), fatal(x) {}

std::string My_Exception::What() const
{
	return message;
}

bool My_Exception::Fatal() const
{
	return fatal;
}

std::ostream & operator << (std::ostream & out, const My_Exception & exception)
{
	out << "Exception: \""<< exception.message << "\" ";
	if(exception.Fatal())
	{
		out << "not ";
	}
	out << "fatal";
	return out;
}

int main()
{

	My_Exception ex("MEOW");

	std::cout << ex.What() << std::endl;
	std::cout << ex << std::endl;
	return 0;
}
