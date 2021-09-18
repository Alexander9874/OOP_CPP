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

		void PrintTotal();

		void SetCoeff(double, double);

		Lem_Bouta(double, double);
		Lem_Bouta();

		string WhatType();
		void PolarCoeff(double&, double&);
		double FindRadius(double);
		double FindSquare();
		char* TextPolarEquation();
};

#endif
