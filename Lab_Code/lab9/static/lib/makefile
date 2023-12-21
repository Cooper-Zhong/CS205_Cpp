# SOURCE = $(wildcard $(SRC)/*.cpp)

OBJS = $(patsubst %.cpp, %.o, $(wildcard ./*.cpp))

TARGET = libmylib.a
CXX = g++


CFLAGS = -Wall -g -std=c++11
CXXFlAGES = $(CFLAGS) -o3

$(TARGET): $(OBJS)
	ar -r $(TARGET) $^

%.o: %.cpp
	$(CXX) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o $(TARGET)