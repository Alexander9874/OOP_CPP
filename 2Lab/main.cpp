//#include "source_header.h"
#include "dialog_header.h"

//Dialog_t Dialogs[7] = {Dialog_SetCoeff, Dialog_PrintTotal, Dialog_PolarCoeff, Dialog_WhatType, Dialog_FindSquare, Dialog_FindRadius, Dialog_TextPolarEquation};

int main()
{
	Lem_Bouta* Obj = new Lem_Bouta;
	int choice = 0;
	while(1)
	{
		choice = Dialog_Main();
		if(choice == -1)
		{
			delete Obj;
			return -1;
		}
		if(!choice)
		{
			break;
		}
		try
		{
			Dialogs[choice - 1](Obj);
		}
		catch(int x)
		{
			delete Obj;
			return -1;
		}
	}
	delete Obj;
	return 0;
}
