#!/usr/bin/make -f

BIN:=pc2m
BIN_DEP:=pointscloud_reader.cpp main.cpp
BIN_OBJ:=$(BIN_DEP:%.cpp=%.o)

INSTALL_DIR:=./$(BIN)

CC=$(shell which g++)
GDB=$(shell which gdb)
VALGRIND=$(shell which valgrind)
STRIP=$(shell which strip)

CFLAGS=-Wall --std=c++17 $(shell pkg-config --cflags gdal openscenegraph) -g
LDFLAGS=$(shell pkg-config --libs gdal openscenegraph) -lstdc++fs

.PHONY: clean

all: $(BIN)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS)

$(BIN): $(BIN_OBJ)
	$(CC) -o $(BIN) $(BIN_OBJ) $(LDFLAGS)
clean:
	rm -f $(BIN) $(BIN_OBJ)
