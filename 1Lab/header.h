#ifndef HEADER_H
#define HEADER_H

namespace mySpace
{
	struct Line
	{
		int num;
		double* var;
	}

	template <class T>
	int getNum(T &x)
	{
		std::cin >> x;
		if (!std::cin.())
		{
			return -1;
		}
		return 1;
	}

	inline void swap(double &first, double &last)
	{
		double tmp = first;
		first = last;
		last = tmp;
	}

	Line* fill(int , double*);

}
