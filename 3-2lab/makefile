CFE=-Wall -Wextra -pedantic -Weffc++ -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor -Wold-style-cast -Wconversion -Wsign-conversion -Winit-self -Wunreachable-code
CF=-Wall -Wextra -g
GT=-lgtest -lgtest_main -lpthread -D G_TEST

make: LIBRARIES REORDER TEST DIALOG


unmake:
	mv ./SOURCE/*.cpp ./SOURCE/*.h ./
	rm -r -f SOURCE LIBRARY INCLUDE
	rm RUN_dialog RUN_test -f	
LIBRARIES:
	rm -r -f LIBRARY INCLUDE
	mkdir LIBRARY INCLUDE
	g++-10 -c PCB.cpp $(CF)
	g++-10 -c My_Exception.cpp $(CF)
	g++-10 -c Dialog.cpp main.cpp $(CF)
	g++-10 -c test.cpp $(CF)
	ar rcs libPCB.a PCB.o
	ar rcs libDialog.a Dialog.o main.o
	ar rcs libMy_Exception.a My_Exception.o
	ar rcs libTest.a test.o
	mv *.a ./LIBRARY
	cp *.h ./INCLUDE
	rm *.o
REORDER:
	rm -r -f SOURCE
	mkdir SOURCE
	mv *.cpp *.h ./SOURCE
TEST:
	g++-10 -L./LIBRARY -I./INCLUDE -lTest -lPCB -lMy_Exception $(GT) $(CF) -o RUN_test
DIALOG:
	g++-10 -L./LIBRARY -I./INCLUDE -lDialog -lPCB -lMy_Exception $(CF) -o RUN_dialog 


