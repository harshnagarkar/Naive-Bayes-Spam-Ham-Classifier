run: main.o calculate.o
	g++ -Wall -pedantic -g -o run main.o calculate.o

main.o: main.cpp
	g++ -Wall -pedantic -g -std=c++11 -c main.cpp

calculate.o: calculate.h calculate.cpp
	g++ -Wall -pedantic -g -std=c++11  -c calculate.cpp
clean:
	rm -rf run main.o
