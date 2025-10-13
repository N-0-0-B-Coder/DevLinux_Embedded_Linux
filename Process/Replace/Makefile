CC:= gcc
CFLAGS:= -Wall -Wextra -g

INC:= -I.
SRC:= replace.c

BUILD_DIR:= build/

OBJ:= $(BUILD_DIR)replace.o
TARGET:= $(BUILD_DIR)replace


$(BUILD_DIR):
	mkdir -p $@

$(OBJ): | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INC) -c $(SRC) -o $@

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

all: $(TARGET)
clean:
	rm -rf $(BUILD_DIR)

