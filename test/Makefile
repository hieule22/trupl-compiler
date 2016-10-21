# Makefile for all test units.

ROOTDIR = ..

# GoogleTest setup.

GTEST_DIR = $(ROOTDIR)/third_party/gtest

CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread

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

# Test targets.

CXXFLAGS += -std=c++14 --pedantic

# Utility library tests.

UTIL_SRCS = $(ROOTDIR)/util/*.cc

UTIL_TESTS = container_util_test text_colorizer_test string_util_test

container_util_test: util/container_util_test.cc $(UTIL_SRCS) gtest_main.a
	$(CXX) $(CPPFLAGS) -I$(ROOTDIR) $(CXXFLAGS) -lpthread $^ -o $@ \
	&& ./$@

text_colorizer_test: util/text_colorizer_test.cc $(UTIL_SRCS) gtest_main.a
	$(CXX) $(CPPFLAGS) -I$(ROOTDIR) $(CXXFLAGS) -lpthread $^ -o $@ \
	&& ./$@

string_util_test: util/string_util_test.cc $(UTIL_SRCS) gtest_main.a
	$(CXX) $(CPPFLAGS) -I$(ROOTDIR) $(CXXFLAGS) -lpthread $^ -o $@ \
	&& ./$@

# Token library tests.

TOKEN_SRCS = $(ROOTDIR)/tokens/*.cc

TOKEN_TESTS = token_test keyword_token_test punctuation_token_test \
	      rel_operator_token_test add_operator_token_test \
	      mul_operator_token_test identifier_token_test \
	      number_token_test eof_token_test

token_test: tokens/token_test.cc $(TOKEN_SRCS) gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

keyword_token_test: tokens/keyword_token_test.cc $(TOKEN_SRCS) gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

punctuation_token_test: tokens/punctuation_token_test.cc $(TOKEN_SRCS) \
		        gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

rel_operator_token_test: tokens/rel_operator_token_test.cc $(TOKEN_SRCS) \
			 gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

add_operator_token_test: tokens/add_operator_token_test.cc $(TOKEN_SRCS) \
		         gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

mul_operator_token_test: tokens/mul_operator_token_test.cc $(TOKEN_SRCS) \
			 gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

identifier_token_test: tokens/identifier_token_test.cc $(TOKEN_SRCS) \
		       gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

number_token_test: tokens/number_token_test.cc $(TOKEN_SRCS) gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

eof_token_test: tokens/eof_token_test.cc $(TOKEN_SRCS) gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

# Lexical analyzer tests.

SCANNER_SRCS = $(TOKEN_SRCS) $(UTIL_SRCS) $(ROOTDIR)/scanner/*.cc

SCANNER_TESTS = buffer_test stream_buffer_test file_buffer_test scanner_test \
	        lexical_analyzer_test

buffer_test: scanner/buffer_test.cc $(SCANNER_SRCS) gtest_main.a 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

stream_buffer_test: scanner/stream_buffer_test.cc $(SCANNER_SRCS) gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

file_buffer_test: scanner/file_buffer_test.cc $(SCANNER_SRCS) gtest_main.a 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

scanner_test: scanner/scanner_test.cc $(SCANNER_SRCS) gtest_main.a 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

lexical_analyzer_test: scanner/lexical_analyzer_test.cc $(SCANNER_SRCS) \
		       gtest_main.a 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

test:	$(UTIL_TESTS) $(TOKEN_TESTS) $(SCANNER_TESTS)

clean:
	rm -r *.o *.a *.dSYM $(UTIL_TESTS) $(TOKEN_TESTS) $(SCANNER_TESTS)
