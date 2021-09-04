#include <iostream>
using namespace std;

class fruits
{
	public:
		void count(int x)
		{
			number = x;
		}

		void eat(int x)
		{
			eaten = x;
			number -= eaten;
		}

		int number;
	private:
		int eaten;
};

int main()
{
	fruits apples;
	apples.count(100);
	cout << "We have "<< apples.number << "apples."<<endl;
	apples.eat(55);
//	cout << "We ate" << apples.eaten << "apples" <<endl;
	cout << apples.number << "left.\n";

	return 0;
}
