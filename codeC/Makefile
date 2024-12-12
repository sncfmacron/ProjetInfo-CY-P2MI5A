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

# Compile source files into object files
$(BUILD)/%.o: $(DIR)/%.c $(HEADERS) | $(BUILD)
	@$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the executable
$(EXEC): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

# Target to run the program with passed parameters
run: $(EXEC)
	@./$(EXEC) $(TYPE) $(CONSUMER)

clean:
	rm -f $(BUILD)/*.o $(EXEC) temp/*