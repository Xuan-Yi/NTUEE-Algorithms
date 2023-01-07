.PHONY: all clean run
CC=g++
CFLAGS=-std=c++17 -O3
LDFLAGS=-lstdc++
TARGET=bin/cb

all: $(TARGET)

bin/cb: src/cyclebreaker.cpp src/cyclebreaker.h  src/sort_tool.h
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) -Iinc

clean:
	rm -f $(TARGET)

