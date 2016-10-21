# Makefile for building driver programs.

ROOTDIR = ..
CXXFLAGS += -g -std=c++14 -Wall -Wextra --pedantic

UTIL_SRCS = $(ROOTDIR)/util/*.cc
SCANNER_SRCS = $(ROOTDIR)/scanner/*.cc
TOKEN_SRCS = $(ROOTDIR)/tokens/*.cc

scanner_main: scanner_main.cc $(UTIL_SRCS) $(SCANNER_SRCS) $(TOKEN_SRCS)
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) $^ -o $@

clean:
	rm -r *.dSYM scanner_main


