
CC = g++

CFILES = main.cpp tic.cpp
OBJECTS = main.o tic.o

BINARY = bin

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $^
clean:
	del $(BINARY) $(OBJECTS)