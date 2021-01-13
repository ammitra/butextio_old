CFLAGS = -O
CC = g++

SRC = main.cxx BUTextIO.cc
OBJ = $(SRC:.cc = .o)

BUTextIO: $(OBJ)
	$(CC) $(CFLAGS) -o BUTextIO $(OBJ)

clean:
	rm -f core *.o