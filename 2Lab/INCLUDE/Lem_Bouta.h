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
		void PrintCoeff() const;
		void PrintGeneralEquation() const;
		void PrintEquation() const;
	public:
		double GetM() const;
		double GetC() const;
		double GetDMS() const;
		double GetAS() const;
		double GetBS() const;

		void PrintTotal() const;

		void SetCoeff(double, double);

		Lem_Bouta(double, double);
		Lem_Bouta();

		string WhatType() const;
		void PolarCoeff(double&, double&) const;
		double FindRadius(double) const;
		double FindSquare() const;
		char* TextPolarEquation() const;
};

#endif
