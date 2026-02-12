#!/bin/bash/
CC=gcc
CXX=g++
CFLAGS=-g -Wall -pipe
INC=-I ./
BIN=shm
TAG=shm.o \
	main.o 
$(BIN):$(TAG)
	$(CXX) $(CFLAGS) -o $@ $^
%.o:%.cpp
	$(CXX) $(CFLAGS)  $(INC) -c -o $@ $<
clean:
	rm -f *.o $(BIN)
