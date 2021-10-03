#ifndef PSB_HEADER
#define PSB_HEADER

#include <iostream>
#include <math.h>
#include <cfloat>
#include "Get_Templates.h"

#define INCOMING true
#define OUTGOING false
#define NUM 10

struct Contact
{
	bool type;  				// incoming or outgoing
	double x, y;  				// coordinates on PSB
	bool connection;			// connected or not
	unsigned int another_num;		// another contact number

	//пустой конструктор для инициализации экземпляров и массивов экземпляров структуры (контакта) по умолчанию;
	Contact() = default;
	
	//создание экземпляров структуры (контакта) с инициализацией типом и координатами расположения на плате;
	Contact(bool a, double b, double c) : type(a), x(b), y(c), connection(false) {};
};

class PSB
{
	private:
		Contact * contacts[NUM];
		unsigned int num;
		inline void Connect_Body(unsigned int first, unsigned int second)
	public:
		//пустой конструктор для инициализации экземпляра класса (платы) по умолчанию;
		PSB();

