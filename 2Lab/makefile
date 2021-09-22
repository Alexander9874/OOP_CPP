CFE=-Wall -Wextra -pedantic -Weffc++ -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor -Wold-style-cast -Wconversion -Wsign-conversion -Winit-self -Wunreachable-code
CF=-Wall -Wextra
GT=-lgtest -lgtest_main -lpthread
	
make: LIBRARIES REORDER TEST DIALOG

unmake:
	mv ./SOURCE/*.cpp ./SOURCE/*.h ./
	rm -r -f SOURCE LIBRARY INCLUDE
	rm RUN_dialog RUN_test -f
LIBRARIES:
	rm -r -f LIBRARY INCLUDE
	mkdir LIBRARY INCLUDE
	g++-10 -c Lem_Bouta.cpp $(CF)
	g++-10 -c dialog.cpp main.cpp $(CF)
	g++-10 -c test.cpp $(CF) $(GT)
	ar rcs libLem_Bouta.a Lem_Bouta.o
	ar rcs libdialog.a dialog.o main.o
	ar rcs libtest.a test.o 
	mv libLem_Bouta.a libtest.a libdialog.a ./LIBRARY
	rm Lem_Bouta.o main.o dialog.o test.o
	cp dialog.h Lem_Bouta.h ./INCLUDE
REORDER:
	rm -r -f SOURCE
	mkdir SOURCE
	mv *.cpp *.h ./SOURCE
TEST: 
	g++-10 -L./LIBRARY -I./INCLUDE -ltest -lLem_Bouta -lgtest -lgtest_main -lpthread -o RUN_test
DIALOG: 
	g++-10 -L./LIBRARY -I./INCLUDE -ldialog -lLem_Bouta -o RUN_dialog 
