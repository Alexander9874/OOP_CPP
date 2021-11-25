#ifndef EXCEPTIONS_HEADER
#define EXCEPTIONS_HEADER

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

#endif