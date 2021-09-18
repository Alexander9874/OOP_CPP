test:
	g++-10 test.cpp -Wall -Wextra -lgtest -lgtest_main -lpthread -L./LIBRARY -lsource -o run_test
library:
	rm -r -f LIBRARY
	mkdir LIBRARY
	g++-10 -c source.cpp -o source.o
	ar rcs libsource.a source.o
	mv libsource.a ./LIBRARY
	rm source.o
dialog: library
	g++-10 dialog.cpp main.cpp -Wall -Wextra -L./LIBRARY -lsource -o run_dialog



extra-I-L-example_0f_IandL:
	g++-10 source.cpp test.cpp -Wall -Wextra -L./usr/local/lib -I./usr/local/include -lgtest -lgtest_main
