#include "Restaurant.h"
#include "menu.h"

std::istream & operator >> (std::istream & input, char * & res)
{
        const int buf_size = 81;
        char buf[buf_size], *temp;
        int len = 0, chunk_len, str_len;
        do {
                input.get(buf, buf_size, '\n');
                if (!input.good())
                {
                        return input;
                }
                else if (input.gcount() > 0)
                {
                        chunk_len = strlen(buf);
                        str_len = len + chunk_len;
                        temp = res;
                        res = new char[str_len + 1]; 
                        memcpy(res, temp, len);
                        memcpy(res + len, buf, chunk_len);
                        len = str_len;
                        delete [] temp;
                }
                else
                {
                        input.clear();
                        input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
        } while(input.gcount() == buf_size - 1); 
        if (len > 0)  
        {
                res[len] = '\0';
        }
        else
        {
                res = new char[1];
        }
        return input;
}

std::istream & operator >> (std::istream & input, int * & res)
{
	delete [] res;
	res = new int[1];
	char * str = nullptr;
	input >> str;
	if(input.fail())
	{
		return input;
	}
	int count_arr = 0;
	int tmp = 0;
	bool sign = false;
	int i = 0;
	int count = 0;
	while(1)
	{
		if(str[i] == 32 || str[i] == 9 || str[i] == 0)
		{
			if(count == 0  && sign)
			{
				delete [] str;
				input.setstate(std::ios::failbit);
				return input;
			}
			if(count == 0 && str[i])
			{
				++i;
				continue;
			}
			if(count == 0 && str[i] == 0)
			{
				break;
			}
			int * tmp_arr = res;
			res = new int[count_arr + 2];
			memcpy(res, tmp_arr, count_arr * sizeof(int));
			delete [] tmp_arr;
			res[count_arr++] = tmp;
			tmp = 0;
			count = 0;
			sign = false;
			if(str[i] == 0)
			{
				break;
			}
			++i;
			continue;
		}
		if(count == 0 && str[i] == 45)
		{
			sign = true;
			++i;
			continue;
		}
		if(str[i] < 48 || str[i] > 57)
		{
			input.setstate(std::ios::failbit);
			delete [] str;
			return input;
		}
		if((count > 9) || (count == 9 && (tmp > 214748364 || (tmp = 214748364 && str[i] > 55))))
		{
			tmp = std::numeric_limits<int>::max() - 1;
		}
		else
		{
			tmp = tmp * 10 + str[i] - 48;
		}
		++count;
		++i;
	}
	res[count_arr] = std::numeric_limits<int>::max();
	delete [] str;
	if(count_arr == 0)
	{
		input.setstate(std::ios::failbit);
	}
	return input;
}
	
const char * MAIN_FUNC[] = {"0. Exit", "1. Menu Editor", "2. Start", "3. Report"};
const char * EDITOR_FUNC[] = {"0. Exit", "1. Add", "2. Print", "3. Random", "4. Clear"};
const char * START_FUNC[] = {"0. Exit", "1. Manual", "2. Auto"};
const char * MANUAL_FUNC[] = {"0. Exit", "1. Serve"};

const int MAIN_SIZE = sizeof(MAIN_FUNC) / sizeof(MAIN_FUNC[0]);
const int EDITOR_SIZE = sizeof(EDITOR_FUNC) / sizeof(EDITOR_FUNC[0]);
const int START_SIZE = sizeof(START_FUNC) / sizeof(START_FUNC[0]);
const int MANUAL_SIZE = sizeof(MANUAL_FUNC) / sizeof(MANUAL_FUNC[0]);

class eof_or_crash: public std::exception {
	virtual const char *what() const throw();
};

const char * eof_or_crash::what() const throw()
{
	return "EOF or crash of the stream";
}

void dialog_editor(Restaurant & rest)
{
	int check = 0;
	do {
		check = dialog(EDITOR_FUNC, EDITOR_SIZE);
		switch(check)
		{
			case 0:
				return;
			case 1:
			{
				char * dish_name = nullptr;
				input res = input_type("Enter Dish Name", dish_name);
				if(res == END_OF_FILE || res == CRASH)
				{
					delete [] dish_name;
					throw eof_or_crash();
				}
				if(res == INVALID)
				{
					std::cout << "Incorrect input, repeat" << std::endl;
					delete [] dish_name;
					break;
				}
				rest.Menu_Add(dish_name);
				delete [] dish_name;
				break;
			}
			case 2:
			
				rest.Menu_Print();
				break;
			
			case 3:
			
				rest.Menu_Random();
				break;
			
			case 4:
			
				rest.Menu_Clear();
				break;
			
		}
	} while(check);
}

char * int_to_char_arr(int * arr)
{
        int i = 0;
        char * str = new char[1];
        char * tmp;
        while(arr[i] != std::numeric_limits<int>::max())
        {
                str[i] = arr[i] + 33;
                tmp = str;
                str = new char[++i + 1];
                memcpy(str, tmp, i);
                delete [] tmp;
        }
        str[i] = 0;
        return str;
}

void dialog_manual(Restaurant & rest)
{
	int check = 0;
	do {
		check = dialog(MANUAL_FUNC, MANUAL_SIZE);
		switch(check)
		{
			case 0:
				return;
			case 1:
				rest.Menu_Print();
				char * customer_name = nullptr;
				int * dishes_number = nullptr;
				input res = input_type("Enter Customer Name", customer_name);
				if(res == END_OF_FILE || res == CRASH)
                                {
                                        delete [] customer_name;
                                        throw eof_or_crash();
                                }
                                if(res == INVALID)
                                {
                                        std::cout << "Incorrect input, repeat" << std::endl;
                                        delete [] customer_name;
                                        break;
                                }
				res = input_type("Enter Order, use keys", dishes_number);
				if(res == END_OF_FILE || res == CRASH)
                                {
                                        delete [] dishes_number;
                                        delete [] customer_name;
					throw eof_or_crash();
                                }
                                if(res == INVALID)
                                {
                                        std::cout << "Incorrect input, repeat" << std::endl;
                                        delete [] dishes_number;
                                        delete [] customer_name;
                                        break;
                                }

				char * order = int_to_char_arr(dishes_number);
//:w				std::cout << "ORDER DEBUG:\t\t"<< order << std::endl;
				rest.Manual(customer_name, order);

				delete [] order;
				delete [] customer_name;
				delete [] dishes_number;
		}
	} while(check);
}

void dialog_start(Restaurant & rest)
{
	int check = 0;
	do {
		check = dialog(START_FUNC, START_SIZE);
		switch(check)
		{
			case 0:
				break;
			case 1:
				dialog_manual(rest);
				return;
			case 2:
				rest.Auto();
				return;
		}
	} while(check);
}

void dialog_main(Restaurant & rest)
{
	int check = 0;
	do {
		check = dialog(MAIN_FUNC, MAIN_SIZE);
		switch(check)
		{
			case 0:
				break;
			case 1:
				dialog_editor(rest);
				break;
			case 2:
				dialog_start(rest);
				break;
			case 3:
				rest.Report();
		}
	} while(check);
}

int main()
{	
	Restaurant rest;
	try
	{
		dialog_main(rest);
	}
	catch(std::exception &e)
	{
		rest.Menu_Print();
		rest.Report();
		std::cout << std::endl << e.what() << std::endl;
	}
	return 0;
}
