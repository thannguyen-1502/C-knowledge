CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2 -I.

SRC = main.c arena.c platform.c
OUT = app

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)

.PHONY: all clean
