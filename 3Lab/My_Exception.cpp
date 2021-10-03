#include "My_Exception.h"

My_Exception::My_Exception() : message("Some exception."), fatal(false) {}

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
	if(!exception.Fatal())
	{
		out << "not ";
	}
	out << "fatal";
	return out;
}
#ifdef MY_EXCEPTION_MAIN
int main()
{

	My_Exception ex1("MEOW");
	My_Exception ex2("WOOF", true);
	My_Exception ex3(false, "MOO");

	std::cout << ex1 << std::endl;
	std::cout << ex2 << std::endl;
	std::cout << ex3 << std::endl;
	
	std::cout << std::endl;
	My_Exception ex;
	std::cout << ex << std::endl;

	return 0;
}
#endif
