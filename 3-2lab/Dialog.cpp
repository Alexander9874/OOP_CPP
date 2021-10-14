#include "Dialog.h"

int Dialog_Main()
{
	int choice;
	while(1)
	{
		std::cout << "Choose:\n\t0. Exit\n\t1. Inpute Contact\n\t2. Print PCB Contacts\n\t3. Add Contact\n\t4. Connect Contacts\n\t5. Check Connection\n\t6. Select One Type Contacts\n\t7. Find Trace Lengt\n\t8. Extra(not listed in task)" << std::endl;
		Get_Template(choice);
		if(choice < 9 && choice > -1) break;
		std::cout << "Out of range, repeat." << std::endl;
	}
	return choice;
}

void Dialog_Input_Contact(PCB * pcb)
{
	std::cout << "Execute as:\n\t0. Method\n\t1. Overloaded Operator" << std::endl;
	bool choice;
	Get_Template(choice);
	std::cout << "Enter (bool) TYPE (double) X (double) Y of your new contact" << std::endl;
	if(choice)
	{
		Get_Template(*pcb);
	}
	else
	{
		pcb->Input_Contact();
	}
	std::cout << std::endl;
}

void Dialog_Print_PCB(PCB * pcb)
{
	std::cout << "Execute as:\n\t0. Method\n\t1. Overloaded Operator" << std::endl;
	bool choice;
	Get_Template(choice);
	if(choice)
	{
		std::cout << *pcb;
	}
	else
	{
		pcb->Print_PCB();
	}
}

void Dialog_Add_Contact(PCB * pcb)
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
		*pcb += new_contact;
	}
	else
	{
	pcb->Add_Contact(new_contact);
	}
	std::cout << std::endl;
}

void Dialog_Connect(PCB * pcb)
{
	std::cout << "Execute as:\n\t0. Unsafe Connection\n\t1. Safe Connection" << std::endl;
	bool choice;
	Get_Template(choice);
	std::cout << "Enter two contacts' numbers to connect." << std::endl;
	unsigned int first, second;
	Get_Template(first, second);
	if(choice)
	{
		pcb->Connect_Safe(first, second);
	}
	else
	{
		pcb->Connect_Unsafe(first, second);
	}
	std::cout << std::endl;
}

<<<<<<< HEAD
=======
/*
void Dialog_Correct_Connection(PCB * pcb)
{
	std::cout << "Execute Correction for\n\t0. Single contact\n\t1. Whole PCB" << std::endl;
	bool choice;
	Get_Template(choice);
	if(!choice)
	{
		unsigned int number;
		Get_Template(number);
		pcb->Correct_Connection(number);
	}
	else
	{
		pcb->Correct_Connection();
	}
	std::cout << std::endl;
}
*/

>>>>>>> cd7391ebc1f4980027137b2c7ee0ee1b2efc550b
void Dialog_Check_Connection(PCB * pcb)
{
	std::cout << "Execute Correction for\n\t0. Single contact\n\t1. Whole PCB" << std::endl;
	bool choice, result;
	Get_Template(choice);
	if(choice)
	{
		result = pcb->Check_Connection();
	}
	else
	{
		unsigned int number;
		std::cout << "Enter contact to check connection." << std::endl;
		Get_Template(number);
		result = pcb->Check_Connection(number);
	}
	if(result)
	{
		if(choice)
		{	
			std::cout << "PCB is OK.\n" << std::endl;
			return;
		}
		std::cout << "Contact is OK.\n" << std::endl;
		return;
	}
	std::cout << "Found incorrectly connected contact. PCB is broken.\n" << std::endl;
}

void Dialog_One_Type_Contacts(PCB * pcb)
{
	std::cout << "What type of contacts would you like to select\n\t0. Outgoing\n\t1. Incoming" << std::endl;
	bool choice;
	Get_Template(choice);
	unsigned int int_choice = choice;
	Contact * selection = pcb->One_Type_Contacts(int_choice);
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

void Dialog_PCB_Trace_Length(PCB * pcb)
{
	std::cout << "Enter two contacts' numbers to measure their  trace length." << std::endl;
	unsigned int first, second;
	Get_Template(first, second);
	double length = pcb->PCB_Trace_Length(first, second);
	std::cout << "Trace length is " << length << std::endl;
	std::cout << std::endl;
}

void Extra(PCB * pcb)
{
	std::cout << "Enter index" << std::endl;
	unsigned int index;
	Get_Template(index);
	std::cout << (*pcb)[index].type << std::endl;
	std::cout << (*pcb)[index].x << std::endl;
	std::cout << (*pcb)[index].y << std::endl;
}
