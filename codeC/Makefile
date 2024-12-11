# Compiler and flags

CC = gcc
CFLAGS = -Wall

# Directory containing source files

DIR = .
BUILD = ../temp
EXEC = program_c

# Source and header files

SRC = $(wildcard $(DIR)/*.c)
HEADERS = $(wildcard $(DIR)/*.h)
OBJ = $(patsubst $(DIR)/%.c,$(BUILD)/%.o,$(SRC))

# Main target to create the executable
all: $(EXEC)

# Compile and run the executable

$(BUILD)/%.o: $(DIR)/%.c $(HEADERS) | $(BUILD)
	@$(CC) $(CFLAGS) -c $< -o $@


$(EXEC): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)


run: $(EXEC)
	@./$(EXEC)