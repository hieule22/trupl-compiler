# Makefile for building token classes.

ROOTDIR = ..
CXXFLAGS += -g -std=c++14 -Wall -Wextra --pedantic

# Components of the library.
TOKEN_OBJECTS = token.o keyword_token.o punctuation_token.o \
		rel_operator_token.o add_operator_token.o \
		mul_operator_token.o identifier_token.o \
		number_token.o eof_token.o

all:	$(TOKEN_OBJECTS)

token.o: token.h token.cc
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) -c token.cc

keyword_token.o: keyword_token.h keyword_token.cc token.h
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) -c keyword_token.cc

punctuation_token.o: punctuation_token.h punctuation_token.cc token.h
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) -c punctuation_token.cc

rel_operator_token.o: rel_operator_token.h rel_operator_token.cc token.h
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) -c rel_operator_token.cc

add_operator_token.o: add_operator_token.h add_operator_token.cc token.h
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) -c add_operator_token.cc

mul_operator_token.o: mul_operator_token.h mul_operator_token.cc token.h
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) -c mul_operator_token.cc

identifier_token.o: identifier_token.h identifier_token.cc token.h
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) -c identifier_token.cc

number_token.o: number_token.h number_token.cc token.h
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) -c number_token.cc

eof_token.o: eof_token.h eof_token.cc token.h
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) -c eof_token.cc

clean:
	rm -r *.o
