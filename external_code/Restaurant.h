#ifndef RESTAURANT_HEADER
#define RESTAURANT_HEADER

#include "table.h"
#include <ctime>

class Restaurant
{
	private:
		Table customers;
		Table orders;
		Table menu;

		const static int max_menu_size = 223;

		int menu_size = 0;
		int num = 0;
		char * Name_Generate();
		char * Order_Generate();
	public:
		Restaurant() = default;
		~Restaurant() = default;
		// Menu Editor
		void Menu_Random();
		void Menu_Add(const char * dish_name);
		void Menu_Clear(); 
		void Menu_Print();
		// Auto fill customers and orders table with random values
		void Auto();
		// Manual fill -\\-
		void Manual(const char * customer_name, const char * order);
//		void Manual();
		void Report();
		void Add(const char * customer_name, const char * ordered_dishes);
		void Clear();
		void Delete();
};

#endif