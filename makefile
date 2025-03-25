CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -pthread

TARGET = dining_philosophers

SRC = dining_philosophers.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean 