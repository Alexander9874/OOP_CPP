all: dialog test
	
test:
	g++-10 test.cpp -Wall -Wextra -lgtest -lgtest_main -lpthread -L./LIBRARY -lLem_Bouta -o run_test
library:
	rm -r -f LIBRARY
	mkdir LIBRARY
	g++-10 -c Lem_Bouta.cpp -o Lem_Bouta.o
	ar rcs libLem_Bouta.a Lem_Bouta.o
	mv libLem_Bouta.a ./LIBRARY
	rm Lem_Bouta.o
dialog: library
	g++-10 dialog.cpp main.cpp -Wall -Wextra -L./LIBRARY -lLem_Bouta -o run_dialog
clear:
	rm -r ./LIBRARY
	rm run_test run_dialog


example:
	g++-10 source.cpp test.cpp -Wall -Wextra -L./usr/local/lib -I./usr/local/include -lgtest -lgtest_main
