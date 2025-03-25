
all: main

main: utils.o main.cpp
	g++ utils.o main.cpp -o main

utils.o: utils.cpp utils.hpp
	g++ -c utils.cpp

clean:
	rm utils.o main