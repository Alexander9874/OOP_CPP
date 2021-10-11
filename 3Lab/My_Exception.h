#ifndef MY_EXCEPTION_HEADER
#define MY_EXCEPTION_HEADER

#include <iostream>
	
class My_Exception : public std::exception
{
	private:
		const char * message;
		bool fatal;
	public:
		My_Exception();
		My_Exception(const char *);
		My_Exception(const char *, bool);
		My_Exception(bool, const char *);
		virtual const char* what() const noexcept;
		bool Fatal() const noexcept;
		friend std::ostream & operator << (std::ostream &, const My_Exception &);
	};

#endif
