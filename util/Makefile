# Makefile for building utility classes.

ROOTDIR = ..
CXXFLAGS += -g -std=c++14 -Wall -Wextra --pedantic -pthread

all: text_colorizer.o

text_colorizer.o: text_colorizer.h text_colorizer.cc
	$(CXX) -I$(ROOTDIR) $(CXXFLAGS) -c text_colorizer.cc

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

TESTSUITES = container_util_test text_colorizer_test

container_util_test: container_util_test.cc gtest_main.a
	$(CXX) $(CPPFLAGS) -I$(ROOTDIR) $(CXXFLAGS) -lpthread $^ -o $@ \
	&& ./$@

text_colorizer_test: text_colorizer_test.cc text_colorizer.o gtest_main.a
	$(CXX) $(CPPFLAGS) -I$(ROOTDIR) $(CXXFLAGS) -lpthread $^ -o $@ \
	&& ./$@

test: $(TESTSUITES)

clean:
	rm -rf *.o *.a *.dSYM $(TESTSUITES)
