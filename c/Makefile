
CC = gcc
CFLAGS = $(shell pkg-config --cflags libpmem) -O2
LDFLAGS = $(shell pkg-config --libs libpmem) -O2

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

hello: main.o
	$(CC) -o $@ $< $(LDFLAGS)

clean:
	rm -f main.o hello
