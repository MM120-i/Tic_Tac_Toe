# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Source files and the executable name
SRC = tictactoe.c
EXECUTABLE = tictactoe

# Define the targets and their dependencies
all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXECUTABLE)

# Clean target to remove the executable
clean:
	rm -f $(EXECUTABLE)
