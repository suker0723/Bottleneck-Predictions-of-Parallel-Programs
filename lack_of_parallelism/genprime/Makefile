CC = gcc
CFLAGS = -fopenmp -O3 -Wall -Wextra -std=c99
TARGET1 = genprime_atomic
TARGET2 = genprime_critical
OBJECTS1 = genprime_atomic.o
OBJECTS2 = genprime_critical.o
LIBS = -lm

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(OBJECTS1)
	$(CC) $(CFLAGS) -o $(TARGET1) $(OBJECTS1) $(LIBS)

$(TARGET2): $(OBJECTS2)
	$(CC) $(CFLAGS) -o $(TARGET2) $(OBJECTS2) $(LIBS)

genprime_atomic.o: genprime_atomic.c
	$(CC) $(CFLAGS) -c genprime_atomic.c

genprime_critical.o: genprime_critical.c
	$(CC) $(CFLAGS) -c genprime_critical.c

clean:
	rm -f $(TARGET1) $(TARGET2) $(OBJECTS1) $(OBJECTS2)

.PHONY: all clean
