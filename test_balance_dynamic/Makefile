CXX = g++
CXXFLAGS = -Wall -fopenmp -O3
LIBS = -lm
TARGET = balance_dynamic
OBJ = balance_dynamic.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(OBJ): balance_dynamic.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)
