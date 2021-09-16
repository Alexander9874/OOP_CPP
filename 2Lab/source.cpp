#include "source_header.h"

void Lem_Bouta::PrintGeneralEquation()
{
	cout << "General equation:" << endl;
	cout << "(x^2+y^2)^2-(2*m^2+c)*x^2+(2*m^2-c)*y^2=0\n" << endl;
}

void Lem_Bouta::PrintEquation()
{
	cout << "Your equation:" << endl;
	cout << "(x^2+y^2)^2-(2*" << m << "^2+" << c << ")*x^2+(2*" << m << "^2-" << c << ")*y^2=0\n" << endl;
}

void Lem_Bouta::SetCoeff(double x, double y)
{
	m = x;
	c = y;
	this->FixCoeff();
}

void Lem_Bouta::FixCoeff()
{
	DMS = 2*m*m;
	AS = DMS + c;
	BS = c - DMS;
}

void Lem_Bouta::PrintCoeff()
{
	cout << "m=" << m << " c=" << c << '\n' << endl;
}

void Lem_Bouta::PrintTotal()
{
	this->PrintGeneralEquation();
	this->PrintEquation();
	this->PrintCoeff();
}

Lem_Bouta::Lem_Bouta(double a = 0, double b = 0) : m(a), c(b) 
{
	cout << "Coefficients were setted " << a << " and " << b << '\n' << endl;
	FixCoeff();
}

string Lem_Bouta::WhatType()
{
	if(c > DMS)
	{
		return "Elliptical Lemniscate Bouta";
	}
	if(c < DMS)
	{
		return "Hyperbolic Lemniscate Bouta";
	}
	return "Two Circles";
}

bool Lem_Bouta::PolarCoeff(double &x, double &y)
{
	x = AS;
	if(c >= DMS)
	{
		y = BS;
		return true;
	}
	y = -BS;
	return false;
}

double Lem_Bouta::FindSquare()
{
	if(c > DMS)
	{
		return M_PI/2*(AS+BS);
	}
	if(c < DMS)
	{
		
		return (AS+BS)/2*atan(sqrt(-AS*BS))+sqrt(-AS*BS)/2;
	}
	return M_PI*AS/2;
}

double Lem_Bouta::FindRadius(double f)
{
	if(c > DMS)
	{
		return sqrt(AS*pow(cos(f), 2)+BS*pow(sin(f), 2));
	}
	if(c < DMS)
	{
		return sqrt(AS*pow(cos(f), 2)+BS*pow(sin(f), 2));
	}
	return sqrt(AS*pow(cos(f), 2));
	
}

void Lem_Bouta::TextPolarEquation()
{
	string AS_str = to_string(AS);
	string BS_str = to_string(BS);
	string result = "r^2=" + AS_str + "*cos(f)^2";
	if(c > DMS)
	{
		result += "+" + BS_str + "*sin(f)^2";
	}
	if(c < DMS)
	{
		result += BS_str + "*sin(f)^2";
	}
	cout << result << '\n' << endl;;
}



















