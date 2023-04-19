CC = gcc
CFLAGS = -g -Wall -fopenmp -std=c99
TARGETS = matrix_block_multiply matrix_col_row_sum matrix_multiply matrix_sum
OBJECTS = matrix_block_multiply.o matrix_col_row_sum.o matrix_multiply.o matrix_sum.o

all: $(TARGETS)

matrix_block_multiply: matrix_block_multiply.o
	$(CC) $(CFLAGS) -o matrix_block_multiply matrix_block_multiply.o

matrix_col_row_sum: matrix_col_row_sum.o
	$(CC) $(CFLAGS) -o matrix_col_row_sum matrix_col_row_sum.o

matrix_multiply: matrix_multiply.o
	$(CC) $(CFLAGS) -o matrix_multiply matrix_multiply.o

matrix_sum: matrix_sum.o
	$(CC) $(CFLAGS) -o matrix_sum matrix_sum.o

matrix_block_multiply.o: matrix_block_multiply.c
	$(CC) $(CFLAGS) -c matrix_block_multiply.c

matrix_col_row_sum.o: matrix_col_row_sum.c
	$(CC) $(CFLAGS) -c matrix_col_row_sum.c

matrix_multiply.o: matrix_multiply.c
	$(CC) $(CFLAGS) -c matrix_multiply.c

matrix_sum.o: matrix_sum.c
	$(CC) $(CFLAGS) -c matrix_sum.c

clean:
	rm -f $(OBJECTS) $(TARGETS)
