#ifndef DIALOG_HEADER
#define DIALOG_HEADER

#include <iostream>
#include "Lem_Bouta.h" 

typedef void (*Dialog_t)(Lem_Bouta*);

int Dialog_Main();

void Dialog_SetCoeff(Lem_Bouta*);

void Dialog_FindRadius(Lem_Bouta*);

void Dialog_PrintTotal(Lem_Bouta*);

void Dialog_WhatType(Lem_Bouta*);

void Dialog_PolarCoeff(Lem_Bouta*);

void Dialog_FindSquare(Lem_Bouta*);

void Dialog_TextPolarEquation(Lem_Bouta*);

const Dialog_t Dialogs[] = {Dialog_SetCoeff, Dialog_PrintTotal, Dialog_PolarCoeff, Dialog_WhatType, Dialog_FindSquare, Dialog_FindRadius, Dialog_TextPolarEquation};

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
