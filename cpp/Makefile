PROG_1=read-write
OBJ_1=read-write.o
PROG_2=queue
OBJ_2=queue.o
OBJS=$(OBJ_1) $(OBJ_2)
PROGS=$(PROG_1) $(PROG_2)
CXXFLAGS = $(shell pkg-config --cflags libpmemobj++) -std=c++11 -O2
LDFLAGS = $(shell pkg-config --libs libpmemobj++) -O2
CXX = g++
RM = rm

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(PROGS)

$(PROG_1): $(OBJ_1)
	$(CXX) $< $(LDFLAGS) -o $@

$(PROG_2): $(OBJ_2)
	$(CXX) $< $(LDFLAGS) -o $@


clean:
	$(RM) $(OBJS) $(PROGS)
