#include "Lem_Bouta.h"

double Lem_Bouta::GetM() const
{
	return m;
}

double Lem_Bouta::GetC() const
{
	return c;
}

double Lem_Bouta::GetDMS() const
{
	return DMS;
}

double Lem_Bouta::GetAS() const
{
	return AS;
}

double Lem_Bouta::GetBS() const
{
	return BS;
}

void Lem_Bouta::PrintGeneralEquation() const
{
	cout << "General equation:" << endl;
	cout << "(x^2+y^2)^2-(2*m^2+c)*x^2+(2*m^2-c)*y^2=0\n" << endl;
}

void Lem_Bouta::PrintEquation() const
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
	DMS = 2 * m * m;
	AS = DMS + c;
	BS = c - DMS;
}

void Lem_Bouta::PrintCoeff() const
{
	cout << "m=" << m << " c=" << c << '\n' << endl;
}

void Lem_Bouta::PrintTotal() const
{
	this->PrintGeneralEquation();
	this->PrintEquation();
	this->PrintCoeff();
}

Lem_Bouta::Lem_Bouta(double a, double b) : m(a), c(b) 
{
	cout << "\nCoefficients were setted " << m << " and " << c << '\n' << endl;
	FixCoeff();
}

Lem_Bouta::Lem_Bouta() : m(0), c(0)
{
	cout << "\nCoefficients were setted " << m << " and " << c << '\n' << endl;
	FixCoeff();
}

string Lem_Bouta::WhatType() const
{
	if(c > DMS)
	{
		return "Elliptical Lemniscate Bouta";
	}
	if(c + DMS <= 0)
	{
		return "Point";
	}
	if(c < DMS)
	{
		return "Hyperbolic Lemniscate Bouta";
	}
	return "Double Circle";
}

void Lem_Bouta::PolarCoeff(double &x, double &y) const
{
	x = AS;
	y = BS;
}

double Lem_Bouta::FindSquare() const
{
	if(c + DMS <= 0)
	{
		return 0;
	}
	if(c > DMS)
	{
		return M_PI/2*(AS+BS);
	}
	
	if(c < DMS)
	{
		
		return (AS+BS)/2*atan(sqrt(-AS*BS))+sqrt(-AS*BS)/2;
	}
	return M_PI*(AS)/2;
}

double Lem_Bouta::FindRadius(double f) const
{
	if(c + DMS <= 0)
	{
		return 0;
	}
	if(c != DMS)
	{
		return sqrt(AS*pow(cos(f), 2)+BS*pow(sin(f), 2));
	}
	return sqrt(AS*pow(cos(f), 2));
}

char* Lem_Bouta::TextPolarEquation() const
{
	char str_RS[] = "r^2=";
	char str_COS[] = "*cos(f)^2";
	char str_SIN[] = "*sin(f)^2";
	long unsigned int length = 1 + strlen(str_RS);
	char num[20];
	sprintf(num, "%.2f", AS);
	length += strlen(num);
	sprintf(num, "%.2f", BS);
	length += strlen(num);
	if(AS)
	{
		sprintf(num, "%.2f", AS);
		length += strlen(str_COS) + strlen(num);
	}
	if(BS)
	{
		sprintf(num, "%.2f", AS);
		if(c > DMS && AS)
		{
			length += strlen(num) + strlen(str_SIN) + 1;
		}
		else
		{
			length += strlen(num) + strlen(str_SIN);
		}
	}
	if(!BS && !AS)
	{
		length++;
	}
	char* result = new char[length];
	sprintf(result, "r^2=");
	long unsigned int k = strlen(result);
	if(AS)
	{
		sprintf(result + k, "%.2f*cos(f)^2", AS);
		k = strlen(result);
	}
	if(BS)
	{
		if(!AS || c < DMS)
		{
			sprintf(result + k, "%.2f*sin(f)^2" ,BS);
		}
		else
		{
			sprintf(result + k, "+%.2f*sin(f)^2" ,BS);
		}
	}
	if(!BS && !AS)
	{
		sprintf(result + k, "0");
	}
	return result;
}
