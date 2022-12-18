CC=g++-10
FLAGS=-std=c++20 -Wall -pedantic -Wextra
TEST_LIB=-lgtest -lgtest_main -lpthread

all: matrix test_bin

matrix: matrix.cpp matrix.hpp
	$(CC) $(FLAGS) -c matrix.cpp

test_bin: matrix.o tests.cpp
	$(CC) $(FLAGS) matrix.o tests.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin