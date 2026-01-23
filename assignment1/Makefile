SearchNewBooks: SearchNewBooks.o search.o
	g++ -std=c++20 -Wall -Werror SearchNewBooks.o search.o -o SearchNewBooks

SearchNewBooks.o: SearchNewBooks.cpp Book.h search.h
	g++ -std=c++20 -Wall -Werror -c SearchNewBooks.cpp -o SearchNewBooks.o

tests: tests.o search.o
	g++ -std=c++20 -Wall -Werror tests.o search.o -o tests

tests.o: tests.cpp Book.h search.h
	g++ -std=c++20 -Wall -Werror -c tests.cpp -o tests.o

search.o: search.cpp Book.h search.h
	g++ -std=c++20 -Wall -Werror -c search.cpp -o search.o

run: 
	./SearchNewBooks newbooks.dat request.dat

test: tests
	./tests

clean:
	rm -f *.o SearchNewBooks tests
