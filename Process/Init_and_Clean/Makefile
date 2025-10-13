CC:= gcc
CFLAGS:= -Wall -Wextra -g

INC:= -I.
SRC:= init_and_clean.c

BUILD_DIR:= build/

OBJ:= $(BUILD_DIR)init_and_clean.o
TARGET:= $(BUILD_DIR)init_and_clean


$(BUILD_DIR):
	mkdir -p $@

$(OBJ): | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INC) -c $(SRC) -o $@

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

all: $(TARGET)
clean:
	rm -rf $(BUILD_DIR)

