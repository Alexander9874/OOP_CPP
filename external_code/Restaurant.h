#include "table.h"
#include <ctime>

enum result {OK, BAD};

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
/*
		Restaurant(const Reastaurant &);
		Restaurant(Restaurant &&);
		Restauran & operator = (const Restaurant &);
		Restauran & operator = (Restaurant &&);
*/
		// Menu Editor
		result Menu_Random();
		result Menu_Add(const char * dish_name);
		void Menu_Clear();
		void Menu_Print();
		// Auto fill customers and orders table with random values
		result Auto();
		// Manual fill -\\-
		result Manual(const char * customer_name, const char * order);
		// Print daily report
		void Report();
		// Inside Auto and Manual
		result Add(const char * customer_name, const char * ordered_dishes);
		void Clear();
		void Delete();
};
