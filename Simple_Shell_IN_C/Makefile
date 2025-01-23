# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99

# Source files
SRCS = execute_args.c new_process.c read_line.c read_stream.c shell.c shell_interactive.c shell_no_interactive.c split_line.c builtins.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = shell

# Default target
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Compile each .c file into an object file
%.o: %.c shell.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean