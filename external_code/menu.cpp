#include "menu.h"

int dialog(const char *funcs[], int n)
{
	const char *err = "- MENU - ";
	int choice;
	do {
		std::cout << std::endl << err << std::endl;
		err = "Incorrect input. Try again...";
		for (int i = 0; i < n; i++) {
			std::cout << funcs[i] << std::endl;
		}
		std::cout << "\nMake a choice: ";
		choice = getchar() - '0';
		while (getchar() != '\n') {}
	} while (choice < 0 || choice >= n);
	return choice;
}
void menu()
{
	Table table;
	int c = 0, key;
	do {
		c = dialog(FUNCS, FUNCS_SIZE);
		switch(c) {
			case 0:
				break;
			case 1:
			{
				std::pair<int, char*> item;
				input input_res = input_type("Input key and information:", item);
				if (input_res == END_OF_FILE || input_res == CRASH) {
					std::cout << "\nEnd of file or input crash...\n";
					delete [] item.second;
					c = 0;
					break;
				}
				if (input_res == INVALID) {
					std::cout << "\nIvalid input. Try again...\n";
					delete [] item.second;
					break;
				}
				try {
					table.add(item);
				} catch(std::exception &e) {
					std::cout << std::endl << e.what() << std::endl;
				}
				delete [] item.second;
				break;
			}
			case 2:
			{
				Item item;
				if (input_type("Enter key: ", key) != GOOD) {
					std::cout << "\nEnd of file or input crash...\n";
					c = 0;
					break;
				}
				if (table.search_item(item, key) == SUCCESS) {
					std::cout << "\nItem is found!\n";
				} else {
					std::cout << "\nWrong key!\n";
				}
				break;
			}
			case 3:
			try {
				if (input_type("Enter key: ", key) != GOOD) {
					std::cout << "\nEnd of file or input crash...\n";
					c = 0;
					break;
				}
				const char *info = table.search_info(key);
				if (info) {
					std::cout << "\nInformation: " << info << std::endl;
				} else {
					std::cout << "\nWrong key!\n";
				}
				break;
			} catch(std::exception &e) {
				std::cout << e.what() << std::endl;
			}
			case 4:
				if (input_type("Enter key: ", key) != GOOD) {
					std::cout << "\nEnd of file or input crash...\n";
					c = 0;
					break;
				}
				if (table.delete_item(key) != SUCCESS) {
					std::cout << "\nWrong key!\n";
				}
				break;
			case 5:
				std::cout << std::endl << "- TABLE -" << std::endl;
				std::cout << table << std::endl;
				break;
			case 6:
				table.refresh();
				break;
		}
	} while (c != 0);
}