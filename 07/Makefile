CC=g++-10
FLAGS=-std=c++20 -Wall -pedantic -Wextra
TEST_LIB=-lgtest -lgtest_main -lpthread

all: avlmap test_bin

avlmap: avlmap.cpp avlmap.hpp
	$(CC) $(FLAGS) -c avlmap.cpp

test_bin: avlmap.o tests.cpp
	$(CC) $(FLAGS) avlmap.o tests.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin