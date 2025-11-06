CXX = g++
CXXFLAGS = -std=c++17 -I.

TARGET = main

SOURCES = main.cpp \
	structs/stack/stack.cpp \
	structs/set/hashset.cpp \
	structs/array/array.cpp \
	structs/huffman/huffman.cpp \
	structs/lru/lru.cpp \
	exercise/exercise_1.cpp \
	exercise/exercise_4.cpp \
	exercise/exercise_5.cpp \
	exercise/exercise_7.cpp \
	tests/test.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

rebuild: clean all

.PHONY: all run clean rebuild
