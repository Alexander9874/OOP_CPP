#include "PCB.h"
#include <gtest/gtest.h>

using namespace Printed_Circuit_Board;

TEST(Contact_Constructor, Default_Constructor)
{
	Contact x;
	ASSERT_EQ(x.type, false);
	ASSERT_EQ(x.x, 0);
	ASSERT_EQ(x.y, 0);
	ASSERT_EQ(x.connection, false);
}

TEST(Contact_Constructor, Init_Constructor)
{
	Contact x(true, 98.3431, -0.1);
	ASSERT_EQ(x.type, true);
	ASSERT_NEAR(x.x, 98.34, 0.01);
	ASSERT_NEAR(x.y, -0.1, 0.01);
	ASSERT_EQ(x.connection, false);
}

TEST(PCB_Empty, Throw_No_Contacts)
{
	PCB pcb;
	ASSERT_ANY_THROW(pcb.Print_PCB());
	ASSERT_ANY_THROW(std::cout << pcb);
}

TEST(PCB_Add_Contact, Method)
{
	PCB pcb;
	Contact x(true, 24.9, 211);
	pcb.Add_Contact(x);
	Contact y = pcb[0];
	ASSERT_EQ(y.type, x.type);
	ASSERT_NEAR(y.x, x.x, 0.01);
	ASSERT_NEAR(y.y, x.y, 0.01);
}

TEST(PCB_Add_Contact, Overloaded_Operator)
{
	PCB pcb;
	Contact x(true, -8.832873, 20000.1);
	pcb += x;
	Contact y = pcb[0];
	ASSERT_EQ(y.type, x.type);
	ASSERT_NEAR(y.x, x.x, 0.01);
	ASSERT_NEAR(y.y, x.y, 0.01);
}

TEST(PCB_Add_Contact, Throw_Not_Enough_Space)
{
	PCB pcb;
	Contact contact;
	for(unsigned int i = 0; i < NUM; i++)
	{
		pcb += contact;
	}
	ASSERT_ANY_THROW(pcb.Input_Contact());
	ASSERT_ANY_THROW(std::cin >> pcb);
	ASSERT_ANY_THROW(pcb += contact);
}

TEST(PCB_Connect_Contacts, Safe_Method_OK)
{
	PCB pcb;
	Contact x(true, 0, 0), y(false, 0, 0);
	(pcb += x) += y;
	pcb.Connect_Safe(0, 1);
	ASSERT_EQ(pcb[0].another_num, 1);
	ASSERT_EQ(pcb[1].another_num, 0);
}

TEST(PCB_Connect_Contacts, Safe_Throw_No_Contacts)
{
	PCB pcb;
	ASSERT_ANY_THROW(pcb.Connect_Safe(0, 1));
	Contact contact;
	pcb += contact;
	ASSERT_ANY_THROW(pcb.Connect_Safe(0, 1));
}

TEST(PCB_Connect_Contacts, Safe_Throw_Already_Connected)
{
	PCB pcb;
	Contact c1(true, 0, 0), c2(false, 0, 0), c3(false, 0, 0);
	((pcb += c1) += c2) += c3;
	pcb.Connect_Safe(0, 1);
	ASSERT_ANY_THROW(pcb.Connect_Safe(0, 1));
	ASSERT_ANY_THROW(pcb.Connect_Safe(0, 2));
}

TEST(PCB_Connect_Contacts, Safe_Throw_Same_Type)
{
	PCB pcb;
	Contact x, y;
	(pcb += x) += y;
	ASSERT_ANY_THROW(pcb.Connect_Safe(0, 1));
	ASSERT_ANY_THROW(pcb.Connect_Safe(0, 0));
	ASSERT_ANY_THROW(pcb.Connect_Safe(1, 1));
}

TEST(PCB_Connect_Contacts, Usnafe_Throw_No_Contacts)
{
	PCB pcb;
	ASSERT_ANY_THROW(pcb.Connect_Safe(0, 1));
	Contact contact;
	pcb += contact;
	ASSERT_ANY_THROW(pcb.Connect_Safe(0, 1));
}

TEST(PCB_Check_Connection, All_Right_Contact)
{
	PCB pcb;
	for(unsigned int i = 0; i < NUM; i++)
	{
		Contact contact(i % 2, 0, 0);
		pcb += contact;
	}
	pcb.Connect_Safe(2, 7);
	ASSERT_EQ(true, pcb.Check_Connection(2));
	ASSERT_EQ(true, pcb.Check_Connection(7));
}

TEST(PCB_Check_Connection, All_Right_Total)
{
	PCB pcb;
	for(unsigned int i = 0; i < NUM; i++)
	{
		Contact contact(i % 2, 0, 0);
		pcb += contact;
	}
	pcb.Connect_Safe(1, 8);
	ASSERT_EQ(true, pcb.Check_Connection());
}

TEST(PCB_Check_Connection, False_Connection_Contact)
{
	PCB pcb;
	for(unsigned int i = 0; i < NUM - 1; i++)
	{
		Contact contact(i % 2, 0, 0);
		pcb += contact;
	}
	Contact contact(9, 0, 0);
	contact.connection = true;
	contact.another_num = 4;
	pcb += contact;
	ASSERT_EQ(false, pcb.Check_Connection(4));
}

TEST(PCB_Check_Connection, False_Connection_Total)
{
	PCB pcb;
	for(unsigned int i = 0; i < NUM - 1; i++)
	{
		Contact contact(i % 2, 0, 0);
		pcb += contact;
	}
	Contact contact(9, 0, 0);
	contact.connection = true;
	contact.another_num = 4;
	pcb += contact;
	ASSERT_EQ(false, pcb.Check_Connection());
}

TEST(PCB_Check_Connection, Found_Another_Connection_Contact)
{
        PCB pcb;
        for(unsigned int i = 0; i < NUM; i++)
        {
                Contact contact(i % 2, 0, 0); 
                pcb += contact;
        }
        pcb.Connect_Safe(4, 5); 
        pcb.Connect_Unsafe(1, 4); 
        ASSERT_EQ(false, pcb.Check_Connection(4));
}

TEST(PCB_Check_Connection, Found_Another_Connection_Total)
{
        PCB pcb;
        for(unsigned int i = 0; i < NUM; i++)
        {
                Contact contact(i % 2, 0, 0); 
                pcb += contact;
        }
        pcb.Connect_Safe(0, 9); 
        pcb.Connect_Unsafe(6, 9); 
        ASSERT_EQ(false, pcb.Check_Connection());
}

TEST(PCB_Check_Connection, Another_Doesnt_Connected_Contact)
{
	PCB pcb;
        for(unsigned int i = 0; i < NUM - 1; i++)
        {
                Contact contact(i % 2, 0, 0); 
                pcb += contact;
	}
	Contact contact(1, 0, 0);
	contact.connection = true;
	contact.another_num = 2;
	pcb += contact;
	ASSERT_EQ(false, pcb.Check_Connection(9));
}

TEST(PCB_Check_Connection, Same_Types_Contact)
{
	PCB pcb;
        for(unsigned int i = 0; i < NUM; i++)
        {
                Contact contact(i % 2, 0, 0); 
                pcb += contact;
	}
	pcb.Connect_Unsafe(0, 2);
	pcb.Connect_Unsafe(1, 3);
	ASSERT_EQ(false, pcb.Check_Connection(0));
	ASSERT_EQ(false, pcb.Check_Connection(1));
	ASSERT_EQ(false, pcb.Check_Connection(2));
	ASSERT_EQ(false, pcb.Check_Connection(3));
}

TEST(PCB_Check_Connection, Same_Types_Total)
{
	PCB pcb;
        for(unsigned int i = 0; i < NUM; i++)
        {
                Contact contact(i % 2, 0, 0); 
                pcb += contact;
	}
	pcb.Connect_Unsafe(0, 2);
	ASSERT_EQ(false, pcb.Check_Connection());
}

TEST(PCB_One_Type_Contacts, Method)
{
	PCB pcb;
        for(unsigned int i = 0; i < NUM -1; i++)
        {
                Contact contact(i % 2, 0, 0); 
                pcb += contact;
	}
	unsigned int False = 0, True = 1;
	Contact * TRUE = pcb.One_Type_Contacts(True);
	Contact * FALSE = pcb.One_Type_Contacts(False);
	for(unsigned int i = 0; i < True; i++)
	{
		ASSERT_EQ(TRUE[i].type, true);
	}
	for(unsigned int i = 0; i < False; i++)
	{
		ASSERT_EQ(FALSE[i].type, false);
	}
	delete [] TRUE;
	delete [] FALSE;
}

// в VS и тд должно быть по другому
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result" 
TEST(PCB_One_Type_Contacts, Throw)
{
	PCB pcb;
	unsigned int y = true;
	ASSERT_ANY_THROW(pcb.One_Type_Contacts(y));
}

TEST(PCB_Trace_Length, No_Such_Contacts)
{
	PCB pcb;
	ASSERT_ANY_THROW(pcb.PCB_Trace_Length(0, 1));
	Contact contact;
	pcb += contact;
	ASSERT_ANY_THROW(pcb.PCB_Trace_Length(0, 1));
}

TEST(PCB_Trace_Length, No_Such_Connection)
{
	PCB pcb;
	Contact contact1(true, 0, 0), contact2(false, 0, 0);
	(pcb += contact1) += contact2;
	ASSERT_ANY_THROW(pcb.PCB_Trace_Length(0, 1));
}
#pragma GCC diagnostic pop

TEST(PCB_Trace_Length, method)
{
	PCB pcb;
	Contact contact1(true, 345.342, -567.654);
	Contact contact2(false, 553.345, 465.545);
	(pcb += contact1) += contact2;
	pcb.Connect_Safe(0, 1);
	ASSERT_NEAR(1053.9285, pcb.PCB_Trace_Length(0, 1), 0.01);
}

TEST(PCD_Extra_Method, Operator)
{
	PCB pcb;
	Contact contact(true, 34534.345435, -234324234234234.23423423423423423);
	pcb += contact;
	ASSERT_EQ(contact.type, pcb[0].type);
	ASSERT_NEAR(contact.x, pcb[0].x, 0.01);
	ASSERT_NEAR(contact.y, pcb[0].y, 0.01);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
