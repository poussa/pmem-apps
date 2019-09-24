PROG_1=read-write
OBJ_1=read-write.o
PROG_2=transaction
OBJ_2=transaction.o
OBJS=$(OBJ_1) $(OBJ_2)
PROGS=$(PROG_1) $(PROG_2)
CC = gcc
CFLAGS = $(shell pkg-config --cflags libpmemobj) -O2
LDFLAGS = $(shell pkg-config --libs libpmemobj) -O2

all: $(PROGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(PROG_1): $(OBJ_1)
	$(CC) -o $@ $< $(LDFLAGS)

$(PROG_2): $(OBJ_2)
	$(CC) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(PROGS) $(OBJS)
