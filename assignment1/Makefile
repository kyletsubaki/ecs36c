SearchNewBooks: SearchNewBooks.o search.o
	g++ -std=c++20 -Wall -Werror SearchNewBooks.o search.o -o SearchNewBooks

SearchNewBooks.o: SearchNewBooks.cpp
	g++ -std=c++20 -Wall -Werror -c SearchNewBooks.cpp -o SearchNewBooks.o

search.o: search.cpp
	g++ -std=c++20 -Wall -Werror -c search.cpp -o search.o

clean:
	rm -f SearchNewBooks.o search.o SearchNewBooks