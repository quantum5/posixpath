CXX=g++
CXXFLAGS=-std=c++11

all: test

test: test.o posixpath.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test.cpp: posixpath.h
posixpath.cpp: posixpath.h

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
