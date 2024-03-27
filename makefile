CXX=g++
CXXFLAGS= -g -std=c++11
LDLIBS=`pkg-config --cflags --libs lua-5.1`


all: main 

main: main.cpp parser.o
parser.o: parser.cpp
