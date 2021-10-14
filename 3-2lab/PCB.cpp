#include "PCB.h"

namespace Printed_Circuit_Board
{
//создание экземпляров структуры (контакта) с инициализацией типом и координатами расположения на плате;
	Contact::Contact() : type(false), x(0), y(0), connection(false) {};
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

	PCB::~PCB()
	{
		if(num)
		{
			delete [] contacts;
		}
	}

	PCB::PCB(const PCB & obj) : contacts(nullptr), num(obj.num) 
	{
		if(num)
		{
			contacts = new Contact[num];
			for(unsigned int i = 0; i < num; i++)
			{
				contacts[i] = obj.contacts[i];
			}
		}
	}

	PCB & PCB::operator = (const PCB & obj)
	{
		if(this != &obj)
		{
			if(num)
			{
				delete [] contacts;
			}
			num = obj.num;
			if(num)
			{
				contacts = new Contact[num];
				for(unsigned int i = 0; i < num; i++)
				{
					contacts[i] = obj.contacts[i];
				}
			}
		}
		return *this;
	}

	PCB::PCB(PCB && pcb) : contacts(pcb.contacts), num(pcb.num)
	{
		pcb.contacts = nullptr;
	}

	PCB & PCB::operator = (PCB && pcb) noexcept
	{
		if(this != &pcb)
		{
			if(num)
			{
				delete [] contacts;
			}
			num = pcb.num;
			contacts = pcb.contacts;
			pcb.contacts = nullptr;
		}
		return *this;
	}

//ввод экземпляров структуры (контакта) из входного потока с заданием типа и координат расположения для контакта;	(иными словами добавить контакт с клавиатуры)	(Перегрузка >>)

	void PCB::Expand()
	{
		Contact * new_contacts = new Contact[1 + num];
		for(unsigned int i = 0; i < num; i++)
		{
			new_contacts[i] = contacts[i];
		}
		if(num)
		{
			delete [] contacts;
		}
		contacts = new_contacts;
		num++;
	}

	void PCB::Shrink()
	{
		Contact * new_contacts = new Contact[num - 1];
		for(unsigned int i = 0; i < num - 1; i++)
		{
			new_contacts[i] = contacts[i];
		}
		delete [] contacts;
		contacts = new_contacts;
		num--;
	}

	void PCB::Input_Contact(std::istream & input, std::ostream & output)
	{
		Expand();
		bool tmp_type;
		double tmp_x, tmp_y;
		Get_Template(tmp_type, tmp_x, tmp_y, input, output);
		Contact new_contact(tmp_type, tmp_x, tmp_y);
		contacts[num - 1] = new_contact;
	}

	std::istream & operator >> (std::istream & input, PCB & pcb)
	{
		pcb.Expand();
		input >> pcb.contacts[pcb.num - 1].type >> pcb.contacts[pcb.num - 1].x >> pcb.contacts[pcb.num - 1].y;
		pcb.contacts[pcb.num - 1].connection = false;
		if(input.fail())
		{
			pcb.Shrink();
		}
		return input;
	}

//вывод информации о плате в выходной поток;	(Перегрузка <<)
	void PCB::Print_PCB(std::ostream & output) const
	{
		if(!num)
		{
			output << "PCB is empty.\n";
			return;
		}
		output << "NUM\tTYPE\tX\tY\tCONNECTION" << std::endl;
		for(unsigned int i = 0; i < num; i++)
		{
			output << i << '\t' << contacts[i].type << '\t' << contacts[i].x << '\t' << contacts[i].y << '\t';
			if(contacts[i].connection)
			{
				output << contacts[i].another_num << std::endl;
			}
			else
			{
				output << "none" << std::endl;
			}
		}
		output << std::endl;
	}
		
	std::ostream & operator << (std::ostream & output, const PCB & pcb)
	{
		if(!pcb.num)
		{
			output << "PCB is empty.\n";
			return output;
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
		Expand();
		contacts[num - 1] = new_contact;
	}

	PCB & PCB::operator += (Contact new_contact)
	{
		Expand();
		contacts[num - 1] = new_contact;
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

	bool PCB::Check_Connection(unsigned int number) const
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
					return false;
				}
			}
			for(unsigned int i = another_num + 1; i < num; i++)
			{
				if(contacts[i].connection && contacts[i].another_num == number)
				{
					return false;
				}
			}
			if(!contacts[another_num].connection)
			{
				return false;
			}
			else
			{
				if(contacts[another_num].another_num == number)
				{
					if(contacts[another_num].type == contacts[number].type)
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
		}
		return true;
	}

	bool PCB::Check_Connection() const
	{
		for(unsigned int i = 0; i < num; i++)
		{
			if(contacts[i].connection == false)
			{
				for(unsigned int j = i + 1; j < num; j++)
				{
					if(contacts[j].connection && contacts[j].another_num == i)
					{
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
						return false;
					}
				}
				if(!contacts[another_num].connection)
				{
					return false;
				}
				else
				{
					if(contacts[another_num].another_num == i)
					{
						if(contacts[another_num].type == contacts[i].type)
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				for(unsigned int j = another_num + 1; j < num; j++)
				{
					if(contacts[j].connection && contacts[j].another_num == i)
					{
						return false;
					}
				}
			}
		}
		return true;
	}

//выделить группу контактов заданного типа;
//получает аргумент типа unsigned int (подразумеваемый true или false) после завершения меняет его значение на колличество элементов массива
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
		if(!contacts[first].connection || !contacts[second].connection || contacts[first].another_num != second || contacts[second].another_num != first)
		{
			throw My_Exception("No such connection.");
		}
		if(!(Check_Connection(first) && Check_Connection(second)))
		{
			throw My_Exception("Incorrect connection.");
		}
		return sqrt(pow((contacts[first].x - contacts[second].x), 2) + pow((contacts[first].y - contacts[second].y), 2));
	}

	Contact & PCB::operator [](unsigned int index) const
	{
		if(!(index < num))
		{
			throw My_Exception("No such contacts.");
		}
		return this->contacts[index];
	}
}
