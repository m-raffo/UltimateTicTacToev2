# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
 
CC = g++
CFLAGS = -Wall -g
 
# ****************************************************
# Targets needed to bring the executable up to date
 
main: main.o GameBoard.o Node.o MCTS.o
	$(CC) $(CFLAGS) -o main main.o GameBoard.o Node.o MCTS.o
 
# The main.o target can be written more simply
 
main.o: main.cpp GameBoard.hpp Node.hpp MCTS.hpp
	$(CC) $(CFLAGS) -c main.cpp
 
GameBoard.o: GameBoard.hpp

Node.o: Node.hpp

MCTS.o: MCTS.hpp
 
test: test_GameBoard.o GameBoard.o
	$(CC) $(CFLAGS) -o test_GameBoard test_GameBoard.o GameBoard.o
	./test_GameBoard

test_GameBoard.o: test/test_GameBoard.cpp GameBoard.hpp
	$(CC) $(CFLAGS) -I $(shell pwd) -c test/test_GameBoard.cpp
