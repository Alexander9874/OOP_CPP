#include <thread>
#include <iostream>
#include <unistd.h>

void func()
{
	std::cout << "MEOW" << std::endl;
	system("dd if=/dev/zero of=/dev/null");
}

void ls()
{
	while(true)
	{
		usleep(500000);
		system("lscpu | grep \"CPU MHz:\"");
//		system("sensors | grep Core");
	}
}

int main()
{
	std::thread thr_1(ls), thr_2(func), thr_3(func), thr_4(func), thr_5(func), thr_6(func), thr_7(func), thr_8(func), thr_9(func);

	thr_1.join();
	thr_2.join();
	thr_3.join();
	thr_4.join();
	thr_5.join();
	thr_6.join();
	thr_7.join();
	thr_8.join();
//	thr_9.join();

	return 0;
}
