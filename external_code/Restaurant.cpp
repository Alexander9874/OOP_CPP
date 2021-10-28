#include "Restaurant.h"

result Restaurant::Add(const char * customer_name, const char * ordered_dishes)
{
	std::pair <int, const char *> customer, order;
	customer.first = num;
	customer.second = customer_name;
	order.first = num;
	order.second = ordered_dishes;
	try
	{
		customers.add(customer);
	}
	catch(std::exception & e)
	{
		std::cout << std::endl << e.what() << std::endl;
		delete [] order.second;
		delete [] customer.second;
		return BAD;
	}
	try
	{
		orders.add(order);
	}
	catch(std::exception & e)
	{
		std::cout << std::endl << e.what() << std::endl;
		customers.delete_item(num);
		delete [] order.second;
		return BAD;
	}
	++num;
	return OK;
}

void Restaurant::Clear()
{
	Table tmp;
	customers = tmp;
	orders = tmp;
	num = 0;
}

char * Restaurant::Name_Generate()
{
	size_t length = std::rand() % 6 + 4;
	char * name = new char[length + 1];
	name[length] = '\0';
	name[0] = 65 + std::rand() % 26;
	for(size_t i = 1; i < length; ++i)
	{
		name[i] = 97 + std::rand() % 26;
	}
	return name;
}

result Restaurant::Menu_Random()
{
	std::srand(std::time(nullptr));
	std::pair<int, const char *> dish;
	for(unsigned int i = 0; i < 15; ++i)
	{
		dish.first = i;
		dish.second = Name_Generate();
		try
		{
			menu.add(dish);
		}
		catch(std::exception &e)
		{
			std::cout << std::endl <<e.what() << std::endl;
			delete [] dish.second;
			menu_size = i + 1;
			return BAD;
		}
	}
	menu_size = 15;
	return OK;
}

result Restaurant::Menu_Add(const char * dish_name)
{
	if(menu_size == max_menu_size)
	{
		std::cout << std::endl << "Not enough space" << std::endl;
		return BAD;
	}
	std::pair<int, const char *> dish(menu_size, dish_name);
	try
	{
		menu.add(dish);
	}
	catch(std::exception &e)
	{
		std::cout << std::endl << e.what() << std::endl;
		delete [] dish.second;
		return BAD;
	}
	++menu_size;
	return OK;
}

void Restaurant::Menu_Clear()
{
	Table tmp;
	menu = tmp;
	menu_size = 0;
}

void Restaurant::Menu_Print()
{
	if(!menu_size)
	{
		std::cout << "Menu is empty" << std::endl;
		return;
	}
	std::cout << std::endl << "\tMENU:" << std::endl;
	std::cout << menu << std::endl;
}

char * Restaurant::Order_Generate()
{
	size_t length = std::rand() % 3 + 1;
	char * order = new char[length + 1];
	order[length] = '\0';
	for(size_t i = 0; i < length; ++i)
	{
		order[i] = 33 + std::rand() % menu_size;
	}
	return order;
}

result Restaurant::Auto()
{
	Clear();
	std::srand(std::time(nullptr));
	int number = std::rand() % 20 + 10;
	for(int i = 0; i < number; ++i)
	{
		const char * customer_name;
		const char * ordered_dishes;
		try
		{
			customer_name = Name_Generate();
			ordered_dishes = Order_Generate();
		}
		catch(std::exception &e)
		{
			delete [] customer_name;
			delete [] ordered_dishes;
			std::cout << std::endl << e.what() << std::endl;
			return BAD;
		}
		if(Add(customer_name, ordered_dishes) == BAD)
		{
			return BAD;
		}
	}
	return OK;
}

result Restaurant::Manual(const char * customer_name, const char * ordered_dishes)
{
	int i = 0;
	while(ordered_dishes[i])
	{
		if(ordered_dishes[i++] >= menu_size)
		{
			std::cout << std::endl << "No such dish on the menu" << std::endl;
			delete [] customer_name;
			delete [] ordered_dishes;
			return BAD;
		}
	}
	if(Add(customer_name, ordered_dishes) == BAD)
	{
		return BAD;
	}
	return OK;
}


void Restaurant::Report()
{
	if(!num)
	{
		std::cout << std::endl << "No reports" << std::endl;
		return;
	}
	std::cout << "Customer\tOrder" << std::endl;
	for(int i = 0; i < num; ++i)
	{
		std::cout << customers.search_info(i);
		const char * order = orders.search_info(i);
		int j = 0;
		while(order[j])
		{
			std::cout << menu.search_info(static_cast<int>(order[j]) - 33) << std::endl; 
		}
	}
	std::cout << std::endl;
}
