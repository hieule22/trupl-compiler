# Makefile for building utility classes.

ROOTDIR = ..
CXXFLAGS += -g -std=c++14 -Wall -Wextra --pedantic -pthread

all: text_colorizer.o string_util.o

text_colorizer.o: text_colorizer.h text_colorizer.cc
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) -c text_colorizer.cc

string_util.o: string_util.h string_util.cc
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) -c string_util.cc
clean:
	rm -rf *.o
