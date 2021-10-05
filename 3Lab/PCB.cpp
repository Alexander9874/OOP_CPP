#include "PCB.h"

namespace Printed_Circuit_Board
{
//создание экземпляров структуры (контакта) с инициализацией типом и координатами расположения на плате;
	Contact::Contact() : type(0), x(0), y(0), connection(false) {};
	Contact::Contact(bool a, double b, double c) : type(a), x(b), y(c), connection(false) {};

// Используется внутри Connect_Safe & Connect_Unsafe
	inline void PCB::Connect_Body(unsigned int first, unsigned int second)
	{
		contacts[first].connection = true;
		contacts[second].connection = true;
		contacts[first].another_num = second;
		contacts[second].another_num = first;
	}

//пустой конструктор для инициализации экземпляра класса (платы) по умолчанию;
	PCB::PCB() : num(0) {};

//ввод экземпляров структуры (контакта) из входного потока с заданием типа и координат расположения для контакта;	(иными словами добавить контакт с клавиатуры)	(Перегрузка >>)
	void PCB::Input_Contact()
	{
		if(num == NUM)
		{
			throw My_Exception("Not enogh space.");
		}
		bool tmp_type;
		double tmp_x, tmp_y;
		Get_Template(tmp_type, tmp_x, tmp_y);
		Contact new_contact(tmp_type, tmp_x, tmp_y);
		contacts[num++] = new_contact;
	}

	std::istream & operator >> (std::istream & input, PCB & pcb)
	{
		if(pcb.num == NUM)
		{
			throw My_Exception("Not enough space.");
		}
		input >> pcb.contacts[pcb.num].type >> pcb.contacts[pcb.num].x >> pcb.contacts[pcb.num].y;
		pcb.contacts[pcb.num].connection = false;
		if(input.good())
		{
			pcb.num++;
		}
		return input;
	}

//вывод информации о плате в выходной поток;	(Перегрузка <<)
	void PCB::Print_PCB() const
	{
		if(!num)
		{
			throw My_Exception("PCB is empty.");
		}
		std::cout << "NUM\tTYPE\tX\tY\tCONNECTION" << std::endl;
		for(unsigned int i = 0; i < num; i++)
		{
			std::cout << i << '\t' << contacts[i].type << '\t' << contacts[i].x << '\t' << contacts[i].y << '\t';
			if(contacts[i].connection)
			{
				std::cout << contacts[i].another_num << std::endl;
			}
			else
			{
				std::cout << "none" << std::endl;
			}
		}
		std::cout << std::endl;
	}
		
	std::ostream & operator << (std::ostream & output, const PCB & pcb)
	{
		if(!pcb.num)
		{
			throw My_Exception("PCB is empty.");
		}
		output << "NUM\tTYPE\tX\tY\tCONNECTION" << std::endl;
		for(unsigned int i = 0; i < pcb.num; i++)
		{
			output << i << '\t' << pcb.contacts[i].type << '\t' << pcb.contacts[i].x << '\t' << pcb.contacts[i].y << '\t';
			if(pcb.contacts[i].connection)
			{
				output << pcb.contacts[i].another_num << std::endl;
			}
			else
			{
				output << "none" << std::endl;
			}
		}
		output << std::endl;
		return output;
	}

//добавить контакт на плате;	(Перегрузка +=)
	void PCB::Add_Contact(Contact new_contact)
	{
		if(num == NUM)
		{
			throw My_Exception("Not enogh space.");
		}
		contacts[num++] = new_contact;
	}

	PCB & PCB::operator += (Contact new_contact)
	{
		if(num == NUM)
		{
			throw My_Exception("Not enogh space.");
		}
		this->contacts[this->num++] = new_contact;
		return *this;
	}

//“установить связь” между двумя указанными контактами (с проверкой корректности);
	void PCB::Connect_Safe(unsigned int first, unsigned int second)
	{
		if(!(first < num && second < num))
		{
			throw My_Exception("No such contacts.");
		}
		if(contacts[first].type == contacts[second].type)
		{
			throw My_Exception("Both contacts have the same type.");
		}
		if(contacts[first].connection || contacts[second].connection)
		{
			throw My_Exception("One of contacts is (or both are) alredy connected.");
		}
		Connect_Body(first, second);
	}
	
	void PCB::Connect_Unsafe(unsigned int first, unsigned int second)
	{
		if(!(first < num && second < num))
		{
			throw My_Exception("No such contacts.");
		}
		Connect_Body(first, second);
	}

//проверка “корректности связи” контакта, указанного его номером (входной контакт может быть связан только с одним выходным контактом, и наоборот);

	//void
	bool
	PCB::Check_Connection(unsigned int number)
	const
	{
		if(!(number < num))
		{
			throw My_Exception("No such contact.");
		}
		if(contacts[number].connection == false)
		{
			for(unsigned int i = 0; i < num; i++)
			{
				if(contacts[i].connection && contacts[i].another_num == number)
				{
					//std::cout << "Incorrect connection between " << number << " and " << i << ". Connection removed." << std::endl;
					//contacts[i].connection = false;
					return false;
				}
			}
		}
		else
		{
			unsigned int another_num = contacts[number].another_num;
			for(unsigned int i = 0; i < another_num; i++)
			{
				if(contacts[i].connection && contacts[i].another_num == number)
				{
					//std::cout << "#incorrect connection between " << number << " and " << i << ". Connection removed." << std::endl;
					//contacts[i].connection = false;
					return false;
				}
			}
			for(unsigned int i = another_num + 1; i < num; i++)
			{
				if(contacts[i].connection && contacts[i].another_num == number)
				{
					//std::cout << "$incorrect connection between " << number << " and " << i << ". Connection removed." << std::endl;
					//contacts[i].connection = false;
					return false;
				}
			}
			if(!contacts[another_num].connection)
			{
				//std::cout << "&incorrect connection between " << number << " and " << another_num << ". Connection removed." << std::endl;
				//contacts[number].connection = false;
				return false;
			}
			else
			{
				if(contacts[another_num].another_num == number)
				{
					if(contacts[another_num].type == contacts[number].type)
					{
						//std::cout << "!incorrect connection between " << number << " and " << another_num << ". Connection removed." << std::endl;
						//contacts[number].connection = false;
						//contacts[another_num].connection = false;
						return false;
					}
				}
				else
				{
						//std::cout << "?incorrect connection between " << number << " and " << another_num << ". Connection removed." << std::endl;
					//contacts[number].connection = false;
					return false;
					}
			}
		}
		return true;
	}

	//void 
	bool
	PCB::Check_Connection()
	const
	{
		for(unsigned int i = 0; i < num; i++)
		{
			if(contacts[i].connection == false)
			{
				for(unsigned int j = i + 1; j < num; j++)
				{
					if(contacts[j].connection && contacts[j].another_num == i)
					{
						//std::cout << "Incorrect connection between " << i << " and " << j << ". Connection removed." << std::endl;
						//contacts[j].connection = false;
						return false;
					}
				}
			}
			else
			{
				unsigned int another_num = contacts[i].another_num;
				for(unsigned int j = i + 1; j < another_num; j++)
				{
					if(contacts[j].connection && contacts[j].another_num == i)
					{
						//std::cout << "Incorrect connection between " << i << " and " << j << ". Connection removed." << std::endl;
						//contacts[j].connection = false;
						return false;
					}
				}
				if(!contacts[another_num].connection)
				{
					//std::cout << "Incorrect connection between " << i << " and " << another_num << ". Connection removed." << std::endl;
					//contacts[i].connection = false;
					return false;
				}
				else
				{
					if(contacts[another_num].another_num == i)
					{
						if(contacts[another_num].type == contacts[i].type)
						{
							//std::cout << "Incorrect connection between " << i << " and " << another_num << ". Connection removed." << std::endl;
							//contacts[i].connection = false;
							//contacts[another_num].connection = false;
							return false;
						}
					}
					else
					{
						//std::cout << "Incorrect connection between " << i << " and " << another_num << ". Connection removed." << std::endl;
						//contacts[i].connection = false;
						return false;
					}
				}
				for(unsigned int j = another_num + 1; j < num; j++)
				{
					if(contacts[j].connection && contacts[j].another_num == i)
					{
						//std::cout << "Incorrect connection between " << i << " and " << j << ". Connection removed." << std::endl;
						//contacts[j].connection = false;
						return false;
					}
				}
			}
		}
		return true;
	}

//выделить группу контактов заданного типа;
	Contact * PCB::One_Type_Contacts(unsigned int &type) const
	{
		bool bool_type = type;
		unsigned int count = 0;
		for(unsigned int i = 0; i < num; i++)
		{
			if(contacts[i].type == bool_type)
			{
				count++;
			}
		}
		if(!count)
		{
			throw My_Exception("No such contacts.");
		}
		Contact * result = new Contact[count];
		type = count;
		count = 0;
		for(unsigned int i = 0; i < num; i++)
		{
			if(contacts[i].type == bool_type)
			{
				result[count++] = contacts[i];
			}
		}
		return result;
	}

//оценить длину трассы между двумя указанными контактами (с проверкой корректности).
	double PCB::PCB_Trace_Length(unsigned int first, unsigned int second) const
	{
		if(!(first < num && second < num))
		{
			throw My_Exception("No such contacts.");
		}
		if((contacts[first].connection && contacts[first].another_num != second) || (contacts[second].connection && contacts[second].another_num != first))
		{
			throw My_Exception("No such connection.");
		}
		if(contacts[first].type == contacts[second].type)
		{
			throw My_Exception("Incorrect connection.");
		}
		return sqrt(pow((contacts[first].x - contacts[second].x), 2) + pow((contacts[first].y - contacts[second].y), 2));
	}

	Contact PCB::operator [](unsigned int index) const
	{
		if(!(index < num))
		{
			throw My_Exception("No such contack.");
		}
		return this->contacts[index];
	}
}
