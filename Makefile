CC=gcc

SRC=$(wildcard src/*.c)

typedarchiver: $(SRC)
	$(CC) $(SRC) -o typedarchiver