.PHONY: all clean run
CC=g++
CFLAGS=-std=c++17 -O3
LDFLAGS=-lstdc++
TARGET=bin/mps lib/compare

all: $(TARGET)

bin/mps: src/maxPlanarSubset.cpp src/MPSC.cpp src/tm_usage.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) -Iinc

lib/compare: lib/compare.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) -Iinc

clean:
	rm -f $(TARGET)

rmout:
	rm -rf outputs/*.out
