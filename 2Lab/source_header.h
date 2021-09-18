#ifndef SOURCE_HEADER
#define SOURCE_HEADER

#include <iostream>
#include <climits>
#include <math.h>
#include <string.h>

#define _USE_MATH_DEFINES

using namespace std;

class Lem_Bouta
{
	private:
		double m, c, DMS, AS, BS;
		void FixCoeff();
		void PrintCoeff();
		void PrintGeneralEquation();
		void PrintEquation();
	public:
		double GetM();
		double GetC();
		double GetDMS();
		double GetAS();
		double GetBS();

		void SetCoeff(double, double);
		void PrintTotal();			//
		Lem_Bouta(double, double);
		Lem_Bouta();
		string WhatType();			//
		bool PolarCoeff(double&, double&);			//
		double FindRadius(double);		
		double FindSquare();			//
		char* TextPolarEquation();		//
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

#endif
