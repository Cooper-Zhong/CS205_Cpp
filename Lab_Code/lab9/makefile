SRC = ./src
SOURCE = $(wildcard $(SRC)/*.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SOURCE))

TARGET = testfiles
INCLUDE = -I ./inc


CXX = g++
CFLAGS = -Wall -g -std=c++11
CXXFlAGES = $(CFLAGS) -o3


$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFlAGES) $< -o $@ $(INCLUDE)

.PHONY: clean
clean:
	rm -f $(SRC)/*.o $(TARGET)