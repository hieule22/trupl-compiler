# Primary project Makefile.

ROOTDIR = .
CXXFLAGS += -g -std=c++14 -Wall -Wextra --pedantic

# Common headers used by all phases.

TOKEN_HEADERS = tokens/*.h

TOKEN_SOURCES = tokens/*token.cc

UTIL_HEADERS = util/container_util.h \
	       util/string_util.h \
               util/text_colorizer.h

UTIL_SOURCES = util/string_util.cc \
	       util/text_colorizer.cc

TRUPLC_OBJECTS = scanner.o

# Lexical analyzer =============================================================

BUFFER_HEADERS = scanner/*buffer.h

BUFFER_SOURCES = scanner/*buffer.cc

scanner.o: scanner/scanner.h scanner/scanner.cc \
	   $(BUFFER_HEADERS) $(TOKEN_HEADERS) $(UTIL_HEADERS)
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) -c scanner/scanner.cc

# Tests ========================================================================

# GoogleTest setup.

GTEST_DIR = $(ROOTDIR)/third_party/gtest

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

TESTSUITES = scanner_test

scanner_test: scanner/scanner_test.cc scanner.o $(BUFFER_SOURCES) \
	      $(TOKEN_SOURCES) $(UTIL_SOURCES) gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(ROOTDIR) -lpthread $^ -o $@ \
	&& ./$@

# Phony targets ================================================================

all: $(TRUPLC_OBJECTS)

test: $(TESTSUITES)

clean:
	rm -rf *.o *.a *.dSYM $(TESTSUITES)
