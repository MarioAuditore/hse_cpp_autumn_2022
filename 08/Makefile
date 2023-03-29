CC=gcc

all: test_bin

test_bin: cjson.c
	$(CC) $(FLAGS) cjson.c -I/usr/include/python3.8/ -fPIC -shared -o cjson.so $(TEST_LIB)

test:
	./test.py

clean:
	rm -f *.o test_bin