#ifndef HEADER_H
#define HEADER_H

#include <climits>
#include <vector>
#include <iostream>


namespace NameSpaceLab1
{
	using namespace std;

	struct Matrix
	{
		int rows;
		int cols;
		double** items;
	};
	
	template <typename T>
	void getSomething(T &x)
	{
		cin >> x;
		if(cin.eof())
		{
			cout << "EOF occured!" << endl;
			throw -1;
		}
		if(cin.fail())
		{
			cout << "Wrong input!" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			throw 0;
		}
	}
	
	void CreateMatrix(Matrix&);
	
	int FillMatrix(Matrix&);

	int DialogCreate(Matrix&);

	void ModifyMatrix(Matrix&);

	void PrintMatrix(Matrix);

	void DeleteMatrix(Matrix);

	vector<int>* MakeVector(Matrix);

	void PrintVector(vector<int>);
}

#endif
