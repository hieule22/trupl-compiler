# Makefile for building lexical analyzer.

ROOTDIR = ..
CXXFLAGS += -g -std=c++14 -Wall -Wextra --pedantic

BUFFER_OBJECTS = buffer.o stream_buffer.o file_buffer.o
BUFFER_HEADERS = buffer.h stream_buffer.h file_buffer.h

TOKEN_HEADERS = $(ROOTDIR)/tokens/*.h
TOKEN_SOURCES = $(ROOTDIR)/tokens/*token.cc

all: buffer.o stream_buffer.o file_buffer.o scanner.o

buffer.o: buffer.h buffer.cc $(ROOTDIR)/util/container_util.h
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) -c buffer.cc

stream_buffer.o: stream_buffer.h stream_buffer.cc buffer.h
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) -c stream_buffer.cc

file_buffer.o: file_buffer.h file_buffer.cc buffer.h stream_buffer.h
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) -c file_buffer.cc

scanner.o: scanner.h scanner.cc $(BUFFER_HEADERS) $(TOKEN_HEADERS) \
	   $(ROOTDIR)/util/container_util.h
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) -c scanner.cc

scanner_main: scanner_main.cc scanner.o $(BUFFER_OBJECTS) $(TOKEN_SOURCES)
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) $^ -o $@

# GoogleTest setup.

GTEST_DIR = ../third_party/gtest

CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -pthread

# All Google Test headers.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Test suites:

TESTSUITES = buffer_test stream_buffer_test file_buffer_test scanner_test

buffer_test: buffer_test.cc buffer.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

stream_buffer_test: stream_buffer_test.cc stream_buffer.o buffer.o \
		    gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

file_buffer_test: file_buffer_test.cc $(BUFFER_OBJECTS) gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

scanner_test: scanner_test.cc scanner.o $(BUFFER_OBJECTS) \
	      $(TOKEN_SOURCES) gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

test: $(TESTSUITES)

clean:
	rm -r *.o *.a *.dSYM scanner_main $(TESTSUITES)
