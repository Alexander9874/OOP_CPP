#include <thread>
#include <iostream>

void func()
{
	std::cout << "MEOW" << std::endl;
	system("dd if=/dev/zero of=/dev/null");
}

int main()
{
	std::thread thr_1(func), thr_2(func);

	thr_1.join();
	thr_2.join();


	return 0;
}
