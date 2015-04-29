# -Wall == all warnings enabled
# -Werror == treat warnings as ERRORS!
CPPFLAGS = --std=c++11 -Wall -Werror -pedantic -DBOOST_TEST_DYN_LINK
LINKFLAGS = --std=c++11 -lboost_unit_test_framework

OUTDIR = .objs

lib_SOURCES = \
	Rectangle.h \
	RectanglesCollection.h

lib_OBJECTS=$(lib_SOURCES:.cpp=.o)

tests_SOURCES = \
	tests_main.cpp \
	Rectangle_Tests.cpp \
	Rectangles_Collection_Tests.cpp

tests_OBJECTS=$(tests_SOURCES:.cpp=.o)

tests_EXECUTABLE = tests_bin

all: tests

%.o : %.c
	$(CXX) -c $(CPPFLAGS) $< -o $@

$(tests_EXECUTABLE): $(tests_OBJECTS) $(lib_OBJECTS)
	$(CXX) -o $@ $(tests_OBJECTS) $(lib_OBJECTS) $(LINKFLAGS)

tests: $(tests_EXECUTABLE)
	./$(tests_EXECUTABLE)

.PHONY: clean

clean:
	- rm *.o
	- rm tests_bin