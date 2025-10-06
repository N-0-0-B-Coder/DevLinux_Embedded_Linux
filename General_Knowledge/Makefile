# Makefile for building static and shared libraries from strutils.h and bstrutils.c

CC := gcc
CFLAGS := -Wall -fPIC #-O2
AR := ar
ARFLAGS := rcs

INC := -Ilib/
INC_BUILD := -Ibuild/
SRC := lib/bstrutils.c

MAIN := main.c
BUILD_DIR := build/

OBJ := $(BUILD_DIR)bstrutils.o
STATIC_LIB := $(BUILD_DIR)libstrutils.a
SHARED_LIB := $(BUILD_DIR)libstrutils.so

all: $(STATIC_LIB) $(SHARED_LIB)

build:
	mkdir -p $(BUILD_DIR)

$(OBJ): $(SRC) lib/strutils.h | build
	$(CC) $(CFLAGS) $(INC) -c $(SRC) -o $(OBJ)

$(STATIC_LIB): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(SHARED_LIB): $(OBJ)
	$(CC) -shared -o $@ $^

	main_static: $(STATIC_LIB) $(MAIN)
		$(CC) $(CFLAGS) $(INC) -L$(BUILD_DIR) -lstrutils $(MAIN) -o $(BUILD_DIR)main_static

	main_shared: $(SHARED_LIB) $(MAIN)
		$(CC) $(CFLAGS) $(INC) -L$(BUILD_DIR) -lstrutils $(MAIN) -o $(BUILD_DIR)main_shared

static: $(STATIC_LIB)

shared: $(SHARED_LIB)

clean:
	rm -rf build

.PHONY: all static shared clean build