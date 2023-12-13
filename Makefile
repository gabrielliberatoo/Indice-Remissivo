CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
BIN_DIR = bin
EXE = $(BIN_DIR)/pa11.out

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(EXE)

$(EXE): $(OBJS) | $(BIN_DIR)
	$(CC) -o $(EXE) $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ -c $<

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(EXE) $(OBJS)

.PHONY: all clean
