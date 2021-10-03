#ifndef DIALOG_HEADER
#define DIALOG_HEADER

#include <iostream>
#include "PSB.h"
#include "My_Exception.h"

int Dialog_Main();

void Dialog_Input_Contact(PSB *);

void Dialog_Print_PSB(PSB *);

void Dialog_Add_Contact(PSB *);

void Dialog_Connect(PSB *);

void Dialog_Correct_Connection(PSB *);

void Dialog_One_Type_Contacts(PSB *);

void Dialog_PSB_Trace_Length(PSB *);

typedef void (* Dialog_t)(PSB *);

const Dialog_t Dialogs[] = {Dialog_Input_Contact, Dialog_Print_PSB, Dialog_Add_Contact, Dialog_Connect, Dialog_Correct_Connection, Dialog_One_Type_Contacts, Dialog_PSB_Trace_Length};

#endif
