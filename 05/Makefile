CC=g++-10
FLAGS=-std=c++20 -Wall -pedantic -Wextra
TEST_LIB=-lgtest -lgtest_main -lpthread

all: test_bin

# bigint: serializer.cpp serializer.hpp
# 	$(CC) $(FLAGS) -c bigint.cpp

test_bin: tests.cpp
	$(CC) $(FLAGS) tests.cpp -o test_bin $(TEST_LIB)

test:
	./test_bin

clean:
	rm -f *.o test_bin