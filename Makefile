flags = -lglut -lGLU -lGL -march=native -funroll-loops -Wall -Wextra -std=c++11 -fopenmp
CXX=g++
CXXFLAGS=-g
all: build

run: build
	./run

build: board.o main.o

main.o: main.cpp 
	@g++ -g main.cpp -Wall -o run  $(flags) $(CXXFLAGS) board.o

board.o: Classes/board.cpp
	@g++ -g Classes/board.cpp -Wall -c $(flags) $(CXXFLAGS) 

clean:
	rm *.o run
