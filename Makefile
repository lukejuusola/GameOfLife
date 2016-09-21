all: gameoflife.o
	g++ --std=c++11 -o GameOfLife main.cpp gameoflife.o
gameoflife.o:
	g++ --std=c++11 -c -o gameoflife.o gameoflife.cpp
clean:
	rm GameOfLife *~