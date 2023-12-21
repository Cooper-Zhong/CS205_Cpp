# SOURCE = $(wildcard $(SRC)/*.cpp)

OBJS = $(patsubst %.cpp, %.o, $(wildcard ./*.cpp))

TARGET = main
CXX = g++

LDFLAGS = -L ./lib
LIBS = -lfunction

CFLAGS = -Wall -g -std=c++11
CXXFlAGES = $(CFLAGS) -o3

$(TARGET): $(OBJS)
	$(CXX) $^ $(LIBS) $(LDFLAGS) -o $@

%.o: %.cpp
	$(CXX) -c $^ -o $@

.PHONY: clean
clean:
	rm -f *.o $(TARGET)