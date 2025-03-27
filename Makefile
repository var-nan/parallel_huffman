
all: main

main: utils.o huffman_serial.o main.o
	g++ -std=c++20 -g utils.o huffman_serial.o main.o -o main

main.o: main.cpp huffman_serial.hpp utils.hpp
	g++ -std=c++20 -g -c main.cpp

huffman_serial.o: huffman_serial.cpp huffman_serial.hpp
	g++ -std=c++20 -g -c huffman_serial.cpp

utils.o: utils.cpp utils.hpp
	g++ -std=c++20 -g -c utils.cpp

clean:
	rm utils.o huffman_serial.o main.o main