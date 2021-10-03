#ifndef PSB_HEADER
#define PSB_HEADER

#include <iostream>
#include <math.h>
#include "Get_Templates.h"
#include "My_Exception.h"

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
	Contact(bool, double, double);
};

class PSB
{
	private:
		Contact * contacts[NUM];
		unsigned int num;
		inline void Connect_Body(unsigned int, unsigned int);
	public:
		//пустой конструктор для инициализации экземпляра класса (платы) по умолчанию;
		PSB();
		~PSB();
		
		//ввод экземпляров структуры (контакта) из входного потока с заданием типа и координат расположения для контакта;	(иными словами добавить контакт с клавиатуры)	(Перегрузка >>)
		void Input_Contact();
		friend std::istream & operator >> (std::istream &, PSB &);

		//вывод информации о плате в выходной поток;	(Перегрузка <<)
		void Print_PSB() const;
		friend std::ostream & operator << (std::ostream &, const PSB &);

		//добавить контакт на плате;	(Перегрузка +=)
		void Add_Contact(Contact*);
		PSB & operator += (Contact *);

		//“установить связь” между двумя указанными контактами (с проверкой корректности);
		void Connect_Safe(unsigned int, unsigned int);
		void Connect_Unsafe(unsigned int, unsigned int);

		//проверка “корректности связи” контакта, указанного его номером (входной контакт может быть связан только с одним выходным контактом, и наоборот);
		void Correct_Connection(unsigned int);
		void Correct_Connection();
		
		//выделить группу контактов заданного типа;
[[nodiscard]]	Contact **  One_Type_Contacts(bool) const;
		
		//оценить длину трассы между двумя указанными контактами (с проверкой корректности).
[[nodiscard]]	double PSB_Trace_Length(unsigned int, unsigned int) const;
};

#endif
