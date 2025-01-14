# Compiler flags for optimization and warnings
opt=-O3 -Wall -std=c2x

# Default target
all: clean altermac

# Build the final executable 'altermac' from the object file
altermac: altermac.o
	cc ${opt} $^ -o $@  

# $^ is the list of dependencies, which is altermac.o

# Compile the object file 'altermac.o' from the C source code
altermac.o: altermac.c
	cc ${opt} -c $^  

# -c compiles the source to an object file

# Clean up previous builds
clean:
	rm -f altermac *.o  # Removes executable and object files
