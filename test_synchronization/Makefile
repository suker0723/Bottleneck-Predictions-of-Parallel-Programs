CXX = g++
CXXFLAGS = -Wall -fopenmp -O2
LIBS = -lm
TARGET = scan_combine
OBJ = scan_combine.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(OBJ): scan_combine.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)
