#include "Dialog.h"

//Dialog_t Dialogs[] = {Dialog_Input_Contact, Dialog_Print_PSB, Dialog_Add_Contact, Dialog_Connect, Dialog_Correct_Connection, Dialog_One_Type_Contacts, Dialog_PSB_Trace_Length};

int main()
{
	PSB* psb = new PSB;
	int choice = 0;
	while(1)
	{
		try
		{
			choice = Dialog_Main();
			if(!choice)
			{
				break;
			}
			Dialogs[choice -1](psb);
		}
		catch(My_Exception &ex)
		{
			std::cout << ex << std::endl;
			if(ex.Fatal())
			{
				delete psb;
				return -1;
			}
		}
		catch(std::bad_alloc &ex)
		{
			std::cout << ex.what() << std::endl;
			delete psb;
			return -1;
		}
	}
	delete psb;
	return 0;
}
