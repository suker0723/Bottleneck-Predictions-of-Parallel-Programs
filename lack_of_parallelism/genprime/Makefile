# Example compiling command:
# gcc -O3 -std=c99 -Wall -fopenmp -o genprime genprimes.c -lm
# Compiler
CC = gcc

# Compiler flags
CFLAGS = -O3 -std=c99 -Wall -fopenmp

# Source files
SRC = gen_prime_atomic.c

SRC2 = gen_prime_critical.c

# Executable name
EXE = gen_prime_atomic

EXE2 = gen_prime_critical

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
