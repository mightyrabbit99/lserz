CFLAGS += -g
CFLAGS += -I../..

BIN1NAME := tester
BIN1OBJS := tester.o trafficserz.o

.PHONY: clean

$(BIN1NAME): $(BIN1OBJS)
	$(CC) -o $@ $^

clean:
	rm -rf *.o $(BIN1NAME)
