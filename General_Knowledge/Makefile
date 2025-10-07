# Makefile for building static and shared libraries from strutils.h and bstrutils.c

CC := gcc
CFLAGS := -Wall -fPIC #-O2
AR := ar
ARFLAGS := rcs

INC_FLAGS := -Ilib/

INC := lib/strutils.h
SRC := lib/bstrutils.c

MAIN := main.c
LIB_DIR := strutils/
LIB_DIR_SHARED := $(LIB_DIR)/shared/
LIB_DIR_STATIC := $(LIB_DIR)/static/
BUILD_DIR := build/

OBJ := $(LIB_DIR)bstrutils.o
STATIC_LIB := $(LIB_DIR_STATIC)libstrutils.a
SHARED_LIB := $(LIB_DIR_SHARED)libstrutils.so
STATIC_APP := $(BUILD_DIR)main_static
SHARED_APP := $(BUILD_DIR)main_shared

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR_SHARED)
	mkdir -p $(LIB_DIR_STATIC)

$(OBJ): $(SRC) $(INC) | $(LIB_DIR)
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $(SRC) -o $(OBJ)

$(STATIC_LIB): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(SHARED_LIB): $(OBJ)
	$(CC) -shared -o $@ $^

$(STATIC_APP): $(MAIN) $(STATIC_LIB) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INC_FLAGS) $(MAIN) -L$(LIB_DIR_STATIC) -lstrutils -o $@

$(SHARED_APP): $(MAIN) $(SHARED_LIB) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INC_FLAGS) $(MAIN) -L$(LIB_DIR_SHARED) -lstrutils -Wl,-rpath,$(PWD)/$(LIB_DIR_SHARED) -o $@

all: $(STATIC_APP) $(SHARED_APP)

static: $(STATIC_APP)

shared: $(SHARED_APP)

clean:
	rm -rf $(BUILD_DIR) $(LIB_DIR)

.PHONY: all static shared clean