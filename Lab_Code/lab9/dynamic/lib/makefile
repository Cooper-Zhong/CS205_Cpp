# SOURCE = $(wildcard $(SRC)/*.cpp)

OBJS = $(patsubst %.cpp, %.o, $(wildcard ./*.cpp))

TARGET = libfunction.so
CXX = g++

# CFLAGS = -Wall -g -std=c++11
# CXXFlAGES = $(CFLAGS) -o3

$(TARGET): $(OBJS)
	$(CXX) -shared -fPIC $^ -o $@ 

# sudo cp $(TARGET) /usr/lib

%.o: %.cpp
	$(CXX) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o $(TARGET) libfunction.so
	sudo rm -f /usr/lib/libfunction.so