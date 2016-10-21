# Makefile for building lexical analyzer.

ROOTDIR = ..
CXXFLAGS += -g -std=c++14 -Wall -Wextra --pedantic

BUFFER_OBJECTS = buffer.o stream_buffer.o file_buffer.o
BUFFER_HEADERS = buffer.h stream_buffer.h file_buffer.h

TOKEN_HEADERS = $(ROOTDIR)/tokens/*.h

all: buffer.o stream_buffer.o file_buffer.o scanner.o

buffer.o: buffer.h buffer.cc $(ROOTDIR)/util/container_util.h \
	  $(ROOTDIR)/util/text_colorizer.h $(ROOTDIR)/util/string_util.h
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) -c buffer.cc

stream_buffer.o: stream_buffer.h stream_buffer.cc buffer.h
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) -c stream_buffer.cc

file_buffer.o: file_buffer.h file_buffer.cc buffer.h stream_buffer.h
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) -c file_buffer.cc

scanner.o: scanner.h scanner.cc $(BUFFER_HEADERS) $(TOKEN_HEADERS) \
	   $(ROOTDIR)/util/container_util.h \
	   $(ROOTDIR)/util/string_util.h \
	   $(ROOTDIR)/util/text_colorizer.h
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) -c scanner.cc

clean:
	rm -r *.o
