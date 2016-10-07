# Makefile for building token classes.

ROOTDIR = ..
SRCDIR = $(ROOTDIR)/tokens
CXXFLAGS += -g -std=c++14 -Wall -Wextra --pedantic

# Components of the library.
token_objects = token.o keyword_token.o punctuation_token.o \
		rel_operator_token.o add_operator_token.o \
		mul_operator_token.o identifier_token.o \
		number_token.o eof_token.o

token_headers = token.h keyword_token.h punctuation_token.h \
		rel_operator_token.h add_operator_token.h \
		mul_operator_token.h identifier_token.h \
		number_token.h eof_token.h

all:	$(token_objects)

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

# Test suites.

token_test.o: token_test.cc token.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -c token_test.cc

token_test: token_test.o token.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

keyword_token_test.o: keyword_token_test.cc keyword_token.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -c keyword_token_test.cc

keyword_token_test: keyword_token_test.o keyword_token.o token.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

punctuation_token_test.o: punctuation_token_test.cc punctuation_token.h \
			  $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -c punctuation_token_test.cc

punctuation_token_test: punctuation_token_test.o punctuation_token.o token.o \
			gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

rel_operator_token_test.o: rel_operator_token_test.cc rel_operator_token.h \
			   $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -c \
	rel_operator_token_test.cc

rel_operator_token_test: rel_operator_token_test.o rel_operator_token.o \
			 token.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

add_operator_token_test.o: add_operator_token_test.cc add_operator_token.h \
			   $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -c \
	add_operator_token_test.cc

add_operator_token_test: add_operator_token_test.o add_operator_token.o token.o \
			 gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

mul_operator_token_test.o: mul_operator_token_test.cc mul_operator_token.h \
			   $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -c \
	mul_operator_token_test.cc

mul_operator_token_test: mul_operator_token_test.o mul_operator_token.o \
			 token.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

identifier_token_test.o: identifier_token_test.cc identifier_token.h \
			 $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -c identifier_token_test.cc

identifier_token_test: identifier_token_test.o identifier_token.o token.o \
		       gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

number_token_test.o: number_token_test.cc number_token.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -c number_token_test.cc

number_token_test: number_token_test.o number_token.o token.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

eof_token_test.o: eof_token_test.cc eof_token.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -c eof_token_test.cc

eof_token_test: eof_token_test.o eof_token.o token.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

testsuites = token_test keyword_token_test punctuation_token_test \
	    rel_operator_token_test add_operator_token_test \
	    mul_operator_token_test identifier_token_test \
	    number_token_test eof_token_test

test:   $(testsuites)

clean:
	rm *.o *.a $(testsuites)
