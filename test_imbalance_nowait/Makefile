CXX = g++
CXXFLAGS = -Wall -fopenmp -O3
LIBS = -lm
TARGET = imbalance_nowait
OBJ = imbalance_nowait.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(OBJ): imbalance_nowait.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)
