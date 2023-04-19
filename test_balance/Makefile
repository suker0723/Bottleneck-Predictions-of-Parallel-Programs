CXX = g++
CXXFLAGS = -Wall -fopenmp -O3
LIBS = -lm
TARGET = balance
OBJ = balance.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(OBJ): balance.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)
