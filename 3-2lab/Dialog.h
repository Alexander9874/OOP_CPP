#ifndef DIALOG_HEADER
#define DIALOG_HEADER

#include <iostream>
#include "PCB.h"
#include "My_Exception.h"

using namespace Printed_Circuit_Board;

int Dialog_Main();

void Dialog_Input_Contact(PCB *);

void Dialog_Print_PCB(PCB *);

void Dialog_Add_Contact(PCB *);

void Dialog_Connect(PCB *);

void Dialog_Check_Connection(PCB *);

void Dialog_One_Type_Contacts(PCB *);

void Dialog_PCB_Trace_Length(PCB *);

void Extra(PCB *);

typedef void (* Dialog_t)(PCB *);

const Dialog_t Dialogs[] = {Dialog_Input_Contact, Dialog_Print_PCB, Dialog_Add_Contact, Dialog_Connect, Dialog_Check_Connection, Dialog_One_Type_Contacts, Dialog_PCB_Trace_Length, Extra};

#endif
