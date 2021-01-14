CFLAGS = -O
CC = g++

SRC = main.cxx BUTextIO.cc DummyCommands.cc
OBJ = $(SRC:.cc = .o)

BUTextIO: $(OBJ)
	$(CC) $(CFLAGS) -o BUTextIO $(OBJ)

clean:
	rm -f core *.o