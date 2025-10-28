CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -Icode
TARGET = social_media

SRC_DIR = code
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /f /q $(SRC_DIR)\*.o $(TARGET).exe 2>nul || true

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
