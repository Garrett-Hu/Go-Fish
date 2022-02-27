CXX = g++
CXX_FLAG = --std=c++11 -g

default: game
#	./game a2.txt b2.txt

game: main.o cards.o
	$(CXX) main.o cards.o -o game

tests: tests.o cards.o
	$(CXX) tests.o cards.o -o tests
	./tests a0.txt b0.txt

main: main.o cards.o
	$(CXX) main.o cards.o -o main

clean:
	/bin/rm *.o