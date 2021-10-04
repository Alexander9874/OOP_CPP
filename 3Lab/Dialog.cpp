#include "Dialog.h"

int Dialog_Main()
{
	int choice;
	while(1)
	{
		std::cout << "Choose:\n\t0. Exit\n\t1. Inpute Contact\n\t2. Print PSB\n\t3. Add Contact\n\t4. Connect Contacts\n\t5. Correct Connection\n\t6. Select One Type Contacts\n\t7. Find Trace Lengt" << std::endl;
		Get_Template(choice);
		if(choice < 8 && choice > -1) break;
		std::cout << "Out of range, repeat." << std::endl;
	}
	return choice;
}

void Dialog_Input_Contact(PSB * psb)
{
	std::cout << "Execute as:\n\t0. Method\n\t1. Overloaded Operator" << std::endl;
	bool choice;
	Get_Template(choice);
	std::cout << "Enter (bool) TYPE (double) X (double) Y of your new contact" << std::endl;
	if(choice)
	{
		Get_Template(*psb);
	}
	else
	{
		psb->Input_Contact();
	}
	std::cout << std::endl;
}

void Dialog_Print_PSB(PSB * psb)
{
	std::cout << "Execute as:\n\t0. Method\n\t1. Overloaded Operator" << std::endl;
	bool choice;
	Get_Template(choice);
	if(choice)
	{
		std::cout << *psb;
	}
	else
	{
		psb->Print_PSB();
	}
}

void Dialog_Add_Contact(PSB * psb)
{
	std::cout << "Execute as:\n\t0. Method\n\t1. Overloaded Operator" << std::endl;
	bool choice;
	Get_Template(choice);
	std::cout << "Enter (bool) TYPE (double) X (double) Y of your new contact" << std::endl;
	bool tmp_type;
	double tmp_x, tmp_y;
	Get_Template(tmp_type, tmp_x, tmp_y);
	Contact new_contact(tmp_type, tmp_x, tmp_y);
	if(choice)
	{
		*psb += new_contact;
	}
	else
	{
	psb->Add_Contact(new_contact);
	}
	std::cout << std::endl;
}

void Dialog_Connect(PSB * psb)
{
	std::cout << "Execute as:\n\t0. Unsafe Connection\n\t1. Safe Connection" << std::endl;
	bool choice;
	Get_Template(choice);
	std::cout << "Enter two contacts' numbers to connect." << std::endl;
	unsigned int first, second;
	Get_Template(first, second);
	if(choice)
	{
		psb->Connect_Safe(first, second);
	}
	else
	{
		psb->Connect_Unsafe(first, second);
	}
	std::cout << std::endl;
}

/*
void Dialog_Correct_Connection(PSB * psb)
{
	std::cout << "Execute Correction for\n\t0. Single contact\n\t1. Whole PSB" << std::endl;
	bool choice;
	Get_Template(choice);
	if(!choice)
	{
		unsigned int number;
		Get_Template(number);
		psb->Correct_Connection(number);
	}
	else
	{
		psb->Correct_Connection();
	}
	std::cout << std::endl;
}
*/

void Dialog_Correct_Connection(PSB * psb)
{
	std::cout << "Execute Correction for\n\t0. Single contact\n\t1. Whole PSB" << std::endl;
	bool choice, result;
	Get_Template(choice);
	if(choice)
	{
		result = psb->Correct_Connection();
	}
	else
	{
		unsigned int number;
		std::cout << "Enter contact to check connection." << std::endl;
		Get_Template(number);
		result = psb->Correct_Connection(number);
	}
	if(result)
	{
		if(choice)
		{	
			std::cout << "PSB is OK.\n" << std::endl;
			return;
		}
		std::cout << "Contact is OK.\n" << std::endl;
		return;
	}
	std::cout << "Found incorrectly connected contact. PSB is broken.\n" << std::endl;
}

void Dialog_One_Type_Contacts(PSB * psb)
{
	std::cout << "What type of contacts would you like to select\n\t0. Outgoing\n\t1. Incoming" << std::endl;
	bool choice;
	Get_Template(choice);
	unsigned int int_choice = choice;
	Contact * selection = psb->One_Type_Contacts(int_choice);
	std::cout << "TYPE\tX\tY\tCONNECTED" << std::endl;
	for(unsigned int i = 0; i < int_choice; i++)
	{
		std::cout << selection[i].type << '\t' << selection[i].x << '\t' << selection[i].y << '\t';
		if(selection[i].connection)
		{
			std::cout << selection[i].another_num << std::endl;
		}
		else
		{
			std::cout << "none" << std::endl;
		}
	}
	delete [] selection;
	std::cout << std::endl;
}

void Dialog_PSB_Trace_Length(PSB * psb)
{
	std::cout << "Enter two contacts' numbers to measure their  trace length." << std::endl;
	unsigned int first, second;
	Get_Template(first, second);
	double length = psb->PSB_Trace_Length(first, second);
	std::cout << "Trace length is " << length << std::endl;
	std::cout << std::endl;
}
