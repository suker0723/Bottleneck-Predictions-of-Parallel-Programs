# Example compiling command:
# gcc -O3 -std=c99 -Wall -fopenmp -o sum_reduction sum_reduction.c -lm
# Compiler
CC = gcc

# Compiler flags
CFLAGS = -O3 -std=c99 -Wall -fopenmp

# Source files
SRC = sum_reduction.c

SRC2 = sum_critical.c

# Executable name
EXE = sum_reduction

EXE2 = sum_critical

# Default target
all: $(EXE) $(EXE2)

# Rule for building the executable
$(EXE): $(SRC)
	$(CC) $(CFLAGS) $< -o $@
$(EXE2): $(SRC2)
	$(CC) $(CFLAGS) $< -o $@
# Clean target
clean:
	rm -f $(EXE)
