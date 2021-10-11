#ifndef PCB_HEADER
#define PCB_HEADER

#include <iostream>
#include <math.h>
#include "Get_Templates.h"
#include "My_Exception.h"

namespace Printed_Circuit_Board
{
	
//	#define INCOMING true	// Выходной тип контакта
//	#define OUTGOING false	// Входной тип контакта

	struct Contact
	{
		bool type;  				// Тип контакта (Входной/Выходной)
		double x, y;  				// Координаты на плате
		bool connection;			// true - соединен, false - нет
		unsigned int another_num;		// номер контакта с которым установлено соединение (определено при connection == true)
	
//пустой конструктор для инициализации экземпляров и массивов экземпляров структуры (контакта) по умолчанию;
		Contact();
		
//создание экземпляров структуры (контакта) с инициализацией типом и координатами расположения на плате;
		Contact(bool, double, double);
	};
		
	class PCB
	{
		private:
			char * contacts;	// Указатель а контакты
			unsigned int num;	// Количество контактов в массиве
			inline void Connect_Body(unsigned int, unsigned int);
		public:
//пустой конструктор для инициализации экземпляра класса (платы) по умолчанию;
			PCB();
			
//ввод экземпляров структуры (контакта) из входного потока с заданием типа и координат расположения для контакта;	(иными словами добавить контакт с клавиатуры)	(Перегрузка >>)
			void Input_Contact();
			friend std::istream & operator >> (std::istream &, PCB &);
	
//вывод информации о плате в выходной поток;	(Перегрузка <<)
			void Print_PCB() const;
			friend std::ostream & operator << (std::ostream &, const PCB &);
	
//добавить контакт на плате;	(Перегрузка +=)
			void Add_Contact(Contact);
			PCB & operator += (Contact);
	
//“установить связь” между двумя указанными контактами (с проверкой корректности);
			void Connect_Safe(unsigned int, unsigned int);
			void Connect_Unsafe(unsigned int, unsigned int);
	
//проверка “корректности связи” контакта, указанного его номером (входной контакт может быть связан только с одним выходным контактом, и наоборот);
			
//			void Correct_Connection(unsigned int);
//			void Correct_Connection();
	
	[[nodiscard]]	bool Check_Connection(unsigned int) const;
	[[nodiscard]]	bool Check_Connection() const;
	
//выделить группу контактов заданного типа;
	[[nodiscard]]	Contact * One_Type_Contacts(unsigned int&) const;
			
//оценить длину трассы между двумя указанными контактами (с проверкой корректности).
	[[nodiscard]]	double PCB_Trace_Length(unsigned int, unsigned int) const;
	
	[[nodiscard]]	Contact operator [](unsigned int) const;
	};
}
#endif
