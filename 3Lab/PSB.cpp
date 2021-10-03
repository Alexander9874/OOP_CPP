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
		{
			contacts[first]->connection = true;
			contacts[second]->connection = true;
			contacts[first]->another_num = second;
			contacts[second]->another_num = first;
		}
	public:
		//пустой конструктор для инициализации экземпляра класса (платы) по умолчанию;
		PSB() : num(0) {};
		
		~PSB()
		{
			for(unsigned int i = 0; i < num; i++)
			{
				delete contacts[i];
			}
		}

		//ввод экземпляров структуры (контакта) из входного потока с заданием типа и координат расположения для контакта;	(иными словами добавить контакт с клавиатуры)	(Перегрузка >>)
		//use with catch(bad_alloc) and catch(std::string)
		void Input_Contact()
		{
			if(num == NUM)
			{
				std::cout << "Not enough space.\n" << std::endl;
				return;
			}
			std::cout << "Enter (bool) TYPE (double) X (double) Y of your new contact" << std::endl;
			bool tmp_type;
			double tmp_x, tmp_y;
			Get_Template(tmp_type, tmp_x, tmp_y);
			Contact * new_contact = new Contact(tmp_type, tmp_x, tmp_y);
			contacts[num++] = new_contact;
			std::cout << std::endl;
		}

		//вывод информации о плате в выходной поток;	(Перегрузка <<)
		void Print_PSB()
		{
			if(!num)
			{
				std::cout << "PSB is empty.\n" << std::endl;
				return;
			}
			std::cout << "NUM	TYPE	X	Y	CONNECTION" << std::endl;
			for(unsigned int i = 0; i < num; i++)
			{
				std::cout << i << '\t' << contacts[i]->type << '\t' << contacts[i]->x << '\t' << contacts[i]->y << '\t';
				if(contacts[i]->connection)
				{
					std::cout << contacts[i]->another_num << std::endl;
				}
				else
				{
					std::cout << "none" << std::endl;
				}
			}
			std::cout << std::endl;
		}

		//добавить контакт на плате;	(Перегрузка +=)
		void Add_Contact(Contact* new_contact)
		{
			if(num == NUM)
			{
				std::cout << "Not enough space." << std::endl;
				std::cout << "Your contact was deleted.\n" << std::endl;
				delete new_contact;
				return;
			}
			contacts[num++] = new_contact;
			std::cout << std::endl;
		}


		//“установить связь” между двумя указанными контактами (с проверкой корректности);
		void Connect_Safe(unsigned int first, unsigned int second)
		{
			if(!(first < num && second < num))
			{
				std::cout << "No such contacts." << std::endl;
				return;
			}
			if(contacts[first]->type == contacts[second]->type)
			{
				std::cout << "Both contacts have the same type." << std::endl;
				return;
			}
			if(contacts[first]->connection || contacts[second]->connection)
			{
				std::cout << "One of contacts is (or both are) already connected." << std::endl;
				return;
			}
			Connect_Body(first, second);
		}

		void Connect_Unsafe(unsigned int first, unsigned int second)
		{
			if(!(first < num && second < num))
			{
				std::cout << "No such contacts." << std::endl;
				return;
			}
			Connect_Body(first, second);
		}

		//проверка “корректности связи” контакта, указанного его номером (входной контакт может быть связан только с одним выходным контактом, и наоборот);
		void Correct_Connection(unsigned int number)
		{
			if(!(number < num))
			{
				std::cout << "No such contact." << std::endl;
				return;
			}
			if(contacts[number]->connection == false)
			{
				for(unsigned int i = 0; i < num; i++)
				{
					if(contacts[i]->connection && contacts[i]->another_num == number)
					{
						std::cout << "@incorrect connection between " << number << " and " << i << ". Connection removed." << std::endl;
						contacts[i]->connection = false;
					}
				}
			}
			else
			{
				unsigned int another_num = contacts[number]->another_num;
				for(unsigned int i = 0; i < another_num; i++)
				{
					if(contacts[i]->connection && contacts[i]->another_num == number)
					{
						std::cout << "#incorrect connection between " << number << " and " << i << ". Connection removed." << std::endl;
						contacts[i]->connection = false;
					}
				}
				for(unsigned int i = another_num + 1; i < num; i++)
				{
					if(contacts[i]->connection && contacts[i]->another_num == number)
					{
						std::cout << "$incorrect connection between " << number << " and " << i << ". Connection removed." << std::endl;
						contacts[i]->connection = false;
					}
				}
				if(!contacts[another_num]->connection)
				{
					std::cout << "&incorrect connection between " << number << " and " << another_num << ". Connection removed." << std::endl;
					contacts[number]->connection = false;
				}
				else
				{
					if(contacts[another_num]->another_num == number)
					{
						if(contacts[another_num]->type == contacts[number]->type)
						{
							std::cout << "!incorrect connection between " << number << " and " << another_num << ". Connection removed." << std::endl;
							contacts[number]->connection = false;
							contacts[another_num]->connection = false;
						}
					}
					else
					{
						std::cout << "?incorrect connection between " << number << " and " << another_num << ". Connection removed." << std::endl;
						contacts[number]->connection = false;
					}
				}
			}
		}

		void Correct_Connection()
		{
			for(unsigned int i = 0; i < num; i++)
			{
				if(contacts[i]->connection == false)
				{
					for(unsigned int j = i + 1; j < num; j++)
					{
						if(contacts[j]->connection && contacts[j]->another_num == i)
						{
							std::cout << "Incorrect connection between " << i << " and " << j << ". Connection removed." << std::endl;
							contacts[j]->connection = false;
						}
					}
				}
				else
				{
					unsigned int another_num = contacts[i]->another_num;
					for(unsigned int j = i + 1; j < another_num; j++)
					{
						if(contacts[j]->connection && contacts[j]->another_num == i)
						{
							std::cout << "Incorrect connection between " << i << " and " << j << ". Connection removed." << std::endl;
							contacts[j]->connection = false;
						}
					}
					if(!contacts[another_num]->connection)
					{
						std::cout << "Incorrect connection between " << i << " and " << another_num << ". Connection removed." << std::endl;
						contacts[i]->connection = false;
					}
					else
					{
						if(contacts[another_num]->another_num == i)
						{
							if(contacts[another_num]->type == contacts[i]->type)
							{
								std::cout << "Incorrect connection between " << i << " and " << another_num << ". Connection removed." << std::endl;
								contacts[i]->connection = false;
								contacts[another_num]->connection = false;
							}
						}
						else
						{
							std::cout << "Incorrect connection between " << i << " and " << another_num << ". Connection removed." << std::endl;
							contacts[i]->connection = false;
						}
					}
					for(unsigned int j = another_num + 1; j < num; j++)
					{
						if(contacts[j]->connection && contacts[j]->another_num == i)
						{
							std::cout << "Incorrect connection between " << i << " and " << j << ". Connection removed." << std::endl;
							contacts[j]->connection = false;
						}
					}
				}
			}
		}
		
		//выделить группу контактов заданного типа;
		Contact **  One_Type_Contacts(bool type)
		{
			unsigned int count = 0;
			for(unsigned int i = 0; i < num; i++)
			{
				if(contacts[i]->type == type)
				{
					count++;
				}
			}
			if(!count)
			{
				return nullptr;
			}
			Contact ** result = new Contact * [count + 1];
			result[count] = nullptr;
			count = 0;
			for(unsigned int i = 0; i < num; i++)
			{
				if(contacts[i]->type == type)
				{
					result[count++] = contacts[i];
				}
			}
			return result;
		}
		
		//оценить длину трассы между двумя указанными контактами (с проверкой корректности).
[[nodiscard]]	double PCB_Trace_Length(unsigned int first, unsigned int second)
		{
			if(!(first < num && second < num))
			{
				std::cout << "No such contacts.\n" << std::endl;
				return DBL_MAX;
			}
			if((contacts[first]->connection && contacts[first]->another_num != second) || (contacts[second]->connection && contacts[second]->another_num != first))
			{
				std::cout << "No such connection.\n" << std::endl;
				return DBL_MAX;
			}
			if(contacts[first]->type == contacts[second]->type)
			{
				std::cout << "Incorrect connection.\n" << std::endl;
				return DBL_MAX;
			}
			return sqrt(pow((contacts[first]->x - contacts[second]->x), 2) + pow((contacts[first]->y - contacts[second]->y), 2));
		}
};

int main()
{
	PSB obj;
	obj.Print_PSB();
	try
	{
		obj.Input_Contact();
		obj.Input_Contact();
		for(int i = 0; i < 8; i++)
		{
			Contact * contact = new Contact(i % 2, i, i * 8);
			obj.Add_Contact(contact);
		}
		obj.Print_PSB();
		for(int i = 0; i < 4; i += 2)
		{
			obj.Connect_Safe(i, i + 1);
		}


	}
	catch(std::bad_alloc &msg)
	{
		std::cout << msg.what() << std::endl;
	}
	catch(std::string msg)
	{
		std::cout << msg << std::endl;
	}

std::cout << "MEOW" << std::endl;	
	obj.Connect_Safe(9, 7);
	obj.Connect_Safe(8, 1);
	obj.Connect_Safe(5, 6);
	obj.Connect_Unsafe(8, 1);
	obj.Connect_Unsafe(5, 6);
	obj.Connect_Unsafe(9, 7);

	for(int i = 0; i < 10; i++)
	{
		std::cout << obj.PCB_Trace_Length(i, i + 1) << std::endl;
	}

	obj.Print_PSB();

//	obj.Correct_Connection();
	for(int i = 0; i < NUM; i++)
	{
		obj.Correct_Connection(i);
	}

	obj.Print_PSB();

	Contact ** array = obj.One_Type_Contacts(true);
	int i = 0;
	while(array[i])
	{
		Contact item = *(array[i]);
		std::cout << item.type << '\t' << item.x << '\t' << item.y << '\t';
		if(item.connection)
		{
			 std::cout << item.another_num << std::endl;
		}
		else
		{
			std::cout << "none" << std::endl;
		}
		i++;
	}
	delete [] array;

	array = obj.One_Type_Contacts(false);
	i = 0;

	std::cout << std::endl;

	while(array[i])
	{
		Contact item = *(array[i]);
		std::cout << item.type << '\t' << item.x << '\t' << item.y << '\t';
		if(item.connection)
		{
			 std::cout << item.another_num << std::endl;
		}
		else
		{
			std::cout << "none" << std::endl;
		}
		i++;
	}
	delete [] array;

	return 0;
}
