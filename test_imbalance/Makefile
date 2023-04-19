CXX = g++
CXXFLAGS = -Wall -fopenmp -O3
LIBS = -lm
TARGET = imbalance
OBJ = imbalance.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(OBJ): imbalance.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)
