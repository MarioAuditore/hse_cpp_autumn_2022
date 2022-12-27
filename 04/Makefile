CC=g++-10
FLAGS=-std=c++20 -Wall -pedantic -Wextra
TEST_LIB=-lgtest -lgtest_main -lpthread

all: bigint test_bin

bigint: bigint.cpp bigint.hpp
	$(CC) $(FLAGS) -c bigint.cpp

test_bin: bigint.o tests.cpp
	$(CC) $(FLAGS) bigint.o tests.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin