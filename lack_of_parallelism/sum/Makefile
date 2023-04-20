CC = gcc
CFLAGS = -fopenmp -O3 -Wall -Wextra -std=c99
TARGET1 = sum_critical
TARGET2 = sum_reduction
OBJECTS1 = sum_critical.o
OBJECTS2 = sum_reduction.o
LIBS = -lm

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(OBJECTS1)
	$(CC) $(CFLAGS) -o $(TARGET1) $(OBJECTS1) $(LIBS)

$(TARGET2): $(OBJECTS2)
	$(CC) $(CFLAGS) -o $(TARGET2) $(OBJECTS2) $(LIBS)

sum_critical.o: sum_critical.c
	$(CC) $(CFLAGS) -c sum_critical.c

sum_reduction.o: sum_reduction.c
	$(CC) $(CFLAGS) -c sum_reduction.c

clean:
	rm -f $(TARGET1) $(TARGET2) $(OBJECTS1) $(OBJECTS2)

.PHONY: all clean
