C = gcc
CFLAGS = -g -Wall -Wextra -pedantic
SRC = main.c
BINS = stack.exe
RM = del

clean:
	$(RM) $(BINS)

all:
	$(C) $(CFLAGS) $(SRC) -o $(BINS)

exec: all
	$(BINS)

build: all exec