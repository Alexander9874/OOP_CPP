#include "dialog.h"

int Dialog_Main()
{
	int choice;
	while(1)
	{
		cout << "Chose:\n\t0. exit\n\t1. change coefficients\n\t2. print equation and coefficients\n\t3. print polar coefficient\n\t4. find type\n\t5. find square\n\t6. find radius\n\t7. print polar equation\n>> ";
		try
		{
			getSomething(choice);
		}
		catch(int x)
		{
			if(x) return -1;
			continue;
		}
		if(choice < 8 && choice > -1) break;
		cout << "Out of range, repeat." << endl;
	}
	return choice;
}

void Dialog_SetCoeff(Lem_Bouta* Obj)
{
	double x, y;
	cout << "Enter coefficients of your equation, M and C\n>> ";
	while(1)
	{
		try
		{
			getSomething(x);
			getSomething(y);
		}
		catch(int x)
		{
			if(x) throw 1;
			continue;
		}
		break;
	}
	Obj->SetCoeff(x, y);
	cout << "Successful\n" << endl;
}

void Dialog_FindRadius(Lem_Bouta* Obj)
{
	double f;
	cout << "Enter angle f\n>> ";
	while(1)
	{
		try
		{
			getSomething(f);
		}
		catch(int x)
		{
			if(x) throw 1;
			continue;
		}
		break;
	}
	cout << "Radius is " << Obj->FindRadius(f) << '\n' << endl;
}

void Dialog_PrintTotal(Lem_Bouta* Obj)
{
	Obj->PrintTotal();
}

void Dialog_WhatType(Lem_Bouta* Obj)
{
	cout << "Type is " << Obj->WhatType() << '\n' << endl;
}

/*
void Dialog_PolarCoeff(Lem_Bouta* Obj)
{
	double AS, BS;
	bool x = Obj->PolarCoeff(AS, BS);
	if(!BS)
	{
		cout << "r^2=a^2*cos(f)^2" << endl;
		cout << "a^2=2m^2+c=" << AS << '\n' << endl;
		return;
	}
	if(x)
	{
		cout << "r^2=a^2*cos(f)^2+b^2*sin(f)^2" << endl;
		cout << "a^2=2m^2+c=" << AS << endl;
		cout << "b^2=c-2m^2=" << BS << '\n'<< endl;
		return;
	}
	cout << "r^2=a^2*cos(f)^2-b^2*sin(f)^2" << endl;
	cout << "a^2=2m^2+c=" << AS << endl;
	cout << "b^2=2m^2-c=" << -BS << '\n' << endl;
}
*/

void Dialog_PolarCoeff(Lem_Bouta* Obj)
{
	double AS, BS;
	Obj->PolarCoeff(AS, BS);
	cout << "r^2=A*cos(f)^2+B*cos(f)^2" << endl;
	cout << "A = " << AS << endl;
	cout << "B = " << BS << endl;
}

void Dialog_FindSquare(Lem_Bouta* Obj)
{
	cout << "Square is " << Obj->FindSquare() << '\n' << endl;
}

void Dialog_TextPolarEquation(Lem_Bouta* Obj)
{
	char* str = Obj->TextPolarEquation();
	cout << str << '\n' << endl;
	delete [] str;
}
