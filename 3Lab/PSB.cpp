#include "PSB.h"

Contact::Contact(bool a, double b, double c) : type(a), x(b), y(c), connection(false) {};

inline void PSB::Connect_Body(unsigned int first, unsigned int second)
		{
			contacts[first]->connection = true;
			contacts[second]->connection = true;
			contacts[first]->another_num = second;
			contacts[second]->another_num = first;
		}

//пустой конструктор для инициализации экземпляра класса (платы) по умолчанию;
PSB::PSB() : num(0) {};
PSB::~PSB()
{
	for(unsigned int i = 0; i < num; i++)
	{
		delete contacts[i];
	}
}

//ввод экземпляров структуры (контакта) из входного потока с заданием типа и координат расположения для контакта;	(иными словами добавить контакт с клавиатуры)	(Перегрузка >>)
void PSB::Input_Contact()
{
	if(num == NUM)
	{
		throw My_Exception("Not enogh space.");
	}
	std::cout << "Enter (bool) TYPE (double) X (double) Y of your new contact" << std::endl;
	bool tmp_type;
	double tmp_x, tmp_y;
	Get_Template(tmp_type, tmp_x, tmp_y);
	Contact * new_contact = new Contact(tmp_type, tmp_x, tmp_y);
	contacts[num++] = new_contact;
}

std::istream & operator >> (std::istream & in, PSB & psb)
{
	if(psb.num == NUM)
	{
		throw My_Exception("Not enough space.");
	}
	bool tmp_type;
	double tmp_x, tmp_y;
	std::cout << "Enter (bool) TYPE (double) X (double) Y of your new contact" << std::endl << ">> ";
	while(1)
	{
		in >> tmp_type >> tmp_x >> tmp_y;
		if(in.eof())
		{
			throw My_Exception("EOF occured!", 1);
		}
		if(in.fail())
		{
			std::cout << "Wrong input! Repeat from begining.\n>> ";
			in.clear();
			in.ignore(INT_MAX, '\n');
			continue;
		}
		break;
	}
	Contact* new_contact = new Contact(tmp_type, tmp_x, tmp_y);
	psb.contacts[psb.num++] = new_contact;
	return in;
}

//вывод информации о плате в выходной поток;	(Перегрузка <<)
void PSB::Print_PSB() const
{
	if(!num)
	{
		throw My_Exception("PSB is empty.");
	}
	std::cout << "NUM\tTYPE\tX\tY\tCONNECTION" << std::endl;
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

std::ostream & operator << (std::ostream & out, const PSB & psb)
{
	out << "NUM\tTYPE\tX\tY\tCONNECTION" << std::endl;
	for(unsigned int i = 0; i < psb.num; i++)
	{
		out << i << '\t' << psb.contacts[i]->type << '\t' << psb.contacts[i]->x << '\t' << psb.contacts[i]->y << '\t';
		if(psb.contacts[i]->connection)
		{
			out << psb.contacts[i]->another_num << std::endl;
		}
		else
		{
			out << "none" << std::endl;
		}
	}
	out << std::endl;
	return out;
}

//добавить контакт на плате;	(Перегрузка +=)
void PSB::Add_Contact(Contact* new_contact)
{
	if(num == NUM)
	{
		delete new_contact;
		throw My_Exception("Not enogh space.\nYour contact was deleted.");
	}
	contacts[num++] = new_contact;
}

PSB & PSB::operator += (Contact * new_contact)
{
	if(this->num == NUM)
	{
		delete new_contact;
		throw My_Exception("Not enogh space.\nYour contact was deleted.");
	}
	this->contacts[this->num++] = new_contact;
	return *this;
}

//“установить связь” между двумя указанными контактами (с проверкой корректности);
void PSB::Connect_Safe(unsigned int first, unsigned int second)
{
	if(!(first < num && second < num))
	{
		throw My_Exception("No such contacts.");
	}
	if(contacts[first]->type == contacts[second]->type)
	{
		throw My_Exception("Both contacts have the same type.");
	}
	if(contacts[first]->connection || contacts[second]->connection)
	{
		throw My_Exception("One of contacts is (or both are) alredy connected.");
	}
	Connect_Body(first, second);
}

void PSB::Connect_Unsafe(unsigned int first, unsigned int second)
{
	if(!(first < num && second < num))
	{
		throw My_Exception("No such contacts.");
	}
	Connect_Body(first, second);
}

//проверка “корректности связи” контакта, указанного его номером (входной контакт может быть связан только с одним выходным контактом, и наоборот);
void PSB::Correct_Connection(unsigned int number)
{
	if(!(number < num))
	{
		throw My_Exception("No suc contact.");
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

void PSB::Correct_Connection()
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
Contact **  PSB::One_Type_Contacts(bool type) const
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
		throw My_Exception("No such type contacts.");
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
double PSB::PSB_Trace_Length(unsigned int first, unsigned int second) const
	{
	if(!(first < num && second < num))
	{
		throw My_Exception("No such contacts.");
	}
	if((contacts[first]->connection && contacts[first]->another_num != second) || (contacts[second]->connection && contacts[second]->another_num != first))
	{
		throw My_Exception("No such connection.");
	}
	if(contacts[first]->type == contacts[second]->type)
	{
		throw My_Exception("Incorrect connection.");
	}
	return sqrt(pow((contacts[first]->x - contacts[second]->x), 2) + pow((contacts[first]->y - contacts[second]->y), 2));
}
