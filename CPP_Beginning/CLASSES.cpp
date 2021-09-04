#include <iostream>
using namespace std;

template <class T>
T sum(T a, T b)
{
	return a + b;
}

template <class Z>
class MyClass
{
	private:
		Z first, second;
	public:
		MyClass(Z a, Z b) : first(a), second(b) {}
		Z function();
};

template <class Z>
Z MyClass<Z>::function()
{
	return (first < second ? first : second);
}

class CLASS
{
	private:
		int MEOW, WOOF;
	public:
		CLASS(int a, int b) : MEOW(a), WOOF(b)
		{
			cout << "Hello! " << MEOW << WOOF<< endl;
		}
		~CLASS()
		{
			cout << "Goodbye!\n";
		}
};

int main()
{
	CLASS *OBJECT = new CLASS(12, 23);
	MyClass <double> object(12.21, 432.909);
	delete OBJECT;
	cout << object.function() << endl;
	return 0;
}
