#include <>

#define INCOMMING true
#define OUTGOINNG false
#define NUM 10

struct Contact
{
	bool type;  				// incomming or outgoing
	bool connection;			// connected or not
	double x, y;  				// coordinates on PSB
	unsigned int another_num;		// another contact number

	//пустой конструктор для инициализации экземпляров и массивов экземпляров структуры (контакта) по умолчанию;
	Contact() = default;
	
	//создание экземпляров структуры (контакта) с инициализацией типом и координатами расположения на плате;
	Contact(bool a, double b, double c) : type(a), x(b), y(c), connectioin(false);
};

class PSB
{
	private:
		Contact contacts[NUM];
		unsigned int num;
	public:
		//пустой конструктор для инициализации экземпляра класса (платы) по умолчанию;
		PSB() : num(0);
		
		//ввод экземпляров структуры (контакта) из входного потока с заданием типа и координат расположения для контакта;	
		
		void Print_PSB()
		{
			if(!num)
			{
				std::cout << "Empty." << std::endl;
				return;
			}
			std::cout << "type	x	y" << std::endl;
			for(unsigned int i = 0; i < num; i++)
			{
				std::cout << contacts[i].type << '\t' << contacts[i].x << '\t' << contact[i].y << std::endl;
			}
		}

		//добавить контакт на плате;
		void Add_Contact()
		{
			num++;
		}

		перегр

		//“установить связь” между двумя указанными контактами (с проверкой корректности);


		//проверка “корректности связи” контакта, указанного его номером (входной контакт может быть связан только с одним выходным контактом, и наоборот);

		
		//выделить группу контактов заданного типа;

		//оценить длину трассы между двумя указанными контактами (с проверкой корректности).
};
