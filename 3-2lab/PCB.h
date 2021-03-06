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
//(с помощью оператора new; память задается указателем на char в состоянии класса). Для хранения данных в экземпляре класса не должна использоваться лишняя память.
			char * contacts_char;	// Массив контактов
			unsigned int num;	// Количество контактов в массиве

			inline void Connect_Body(unsigned int, unsigned int) noexcept;
			void Expand();
			void Shrink();
		public:
			
			char test_char; // используется только в тестирование копирования и перемещения

//пустой конструктор для инициализации экземпляра класса (платы) по умолчанию;
			PCB();
			~PCB();
//создание экземпляра класса с его инициализацией другим экземпляром класса (копирующий конструктор);
			PCB(const PCB &);
			PCB(PCB &&);
//переопределение экземпляра класса (с помощью перегруженного оператора присваивания).
			PCB & operator = (const PCB &);
			PCB & operator = (PCB &&) noexcept;

//ввод экземпляров структуры (контакта) из входного потока с заданием типа и координат расположения для контакта;	(иными словами добавить контакт с клавиатуры)	(Перегрузка >>)
			void Input_Contact(std::istream & input = std::cin, std::ostream & output = std::cout);
			friend std::istream & operator >> (std::istream &, PCB &);
	
//вывод информации о плате в выходной поток;	(Перегрузка <<)
			void Print_PCB(std::ostream & output = std::cout) const noexcept;
			friend std::ostream & operator << (std::ostream &, const PCB &) noexcept;
	
//добавить контакт на плате;	(Перегрузка +=)
			void Add_Contact(const Contact &);
			PCB & operator += (const Contact &);
	
//“установить связь” между двумя указанными контактами (с проверкой корректности);
			void Connect_Safe(unsigned int, unsigned int);
			void Connect_Unsafe(unsigned int, unsigned int);
	
//проверка “корректности связи” контакта, указанного его номером (входной контакт может быть связан только с одним выходным контактом, и наоборот);
			
	[[nodiscard]]	bool Check_Connection(unsigned int) const;
	[[nodiscard]]	bool Check_Connection() const noexcept;
	
//выделить группу контактов заданного типа;
	[[nodiscard]]	Contact * One_Type_Contacts(unsigned int&) const;
			
//оценить длину трассы между двумя указанными контактами (с проверкой корректности).
	[[nodiscard]]	double PCB_Trace_Length(unsigned int, unsigned int) const;
//Возвращает ссылку на и-тый контакт, нет в задании. Используется в тестировании
	[[nodiscard]]	Contact & operator [](unsigned int) const;
	};
}
#endif
