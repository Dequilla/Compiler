CC=gcc
CFLAGS=

SOURCE_FILES = main.c
SRC_DIR = src/
BIN_DIR = bin/
OBJ_DIR = obj/

REQ_DIRS = $(BIN_DIR) $(OBJ_DIR)
OBJS = $(patsubst %.c,%.o, $(SOURCE_FILES))
EXEC = DeqCompiler

$(info ----------------------------------------)
$(info Building executable $(EXEC))
$(info ----------------------------------------)

all: directories $(EXEC)

run: all
	$(BIN_DIR)$(EXEC)

directories: 
	mkdir -p $(patsubst /,\, $(REQ_DIRS))

%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $(OBJ_DIR)$@

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(patsubst %,$(OBJ_DIR)%, $^) -o $(BIN_DIR)$@