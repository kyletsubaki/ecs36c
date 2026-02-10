.PHONY: all clean

all: timealgorithms consistentresultverification sortedverification

timealgorithms: timealgorithms.cxx json.hpp insertionsort.cpp mergesort.cpp quicksort.cpp insertionsort.h mergesort.h quicksort.h
	g++ -std=c++20 -Wall -Werror -o timealgorithms timealgorithms.cxx insertionsort.cpp mergesort.cpp quicksort.cpp

consistentresultverification: consistentresultverification.cxx json.hpp
	g++ -std=c++20 -Wall -Werror -o consistentresultverification consistentresultverification.cxx

sortedverification: sortedverification.cxx json.hpp
	g++ -std=c++20 -Wall -Werror -o sortedverification sortedverification.cxx

clean:
	rm -rf timealgorithms consistentresultverification sortedverification