CC := gcc
CFLAGS := -Wall -Wextra -g

INC:= -I.
SRC:= filestat.c

BUILD_DIR:= build/

OBJ:= $(BUILD_DIR)filestat.o
TARGET:= $(BUILD_DIR)filestat

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ): | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INC) -c $(SRC) -o $@

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

all: $(TARGET)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean