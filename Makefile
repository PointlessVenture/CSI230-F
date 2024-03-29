CXX       := g++
CXX_FLAGS := -std=c++17 -ggdb

BIN     := bin
SRC     := src
INCLUDE := include
LIB := lib

LIBRARIES   :=
EXECUTABLE  := dnddriver

SO_NAME := parse

LIB_INSTALL_DIR := /usr/lib/x86_64-linux-gnu
BIN_INSTALL_DIR := /usr/local/bin

all: $(LIB)/lib$(SO_NAME).so $(BIN)/$(EXECUTABLE)

$(LIB)/lib$(SO_NAME).so: $(SRC)/$(SO_NAME)/$(SO_NAME).cpp
	$(CXX) -fPIC -c -Wall -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

$(BIN)/$(EXECUTABLE): $(SRC)/$(EXECUTABLE)/$(EXECUTABLE).cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ -L$(LIB) -l$(SO_NAME)

clean:
	-rm $(BIN)/*
	-rm $(LIB)/*

install:
	cp $(LIB)/lib$(SO_NAME).so $(LIB_INSTALL_DIR)/
	cp $(BIN)/$(EXECUTABLE) $(BIN_INSTALL_DIR)/

remove:
	rm $(LIB_INSTALL_DIR)/lib$(SO_NAME).so
	rm $(BIN_INSTALL_DIR)/$(EXECUTABLE)