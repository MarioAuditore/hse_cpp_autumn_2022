CC=g++-10
FLAGS=-std=c++20 -Wall -pedantic -Werror -Wextra
TEST_LIB=-lgtest -lgtest_main -lpthread

all: token_parser test_bin

token_parser: token_parser.cpp token_parser.hpp
	$(CC) $(FLAGS) -c token_parser.cpp

test_bin: token_parser.o tests.cpp
	$(CC) $(FLAGS) token_parser.o tests.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin