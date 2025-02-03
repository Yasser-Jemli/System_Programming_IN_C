include Makeconfig

# Ensure the obj and bin directories exist
$(shell mkdir -p obj bin)

# Default target
all: $(TARGET)

# Rule to link object files into the final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile source files into object files
obj/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf obj/* bin/*
	rm -rf $(DATABASE_DEFAULT_FILE_NAME)
	rm -rf $(DATABASE_FILE_NAME)

test : 
	./$(TARGET) -n 
	mv $(DATABASE_DEFAULT_FILE_NAME) $(DATABASE_FILE_NAME)
	./$(TARGET) -e $(DATABASE_FILE_NAME) -a yasser,jemli,1,11,manager

# Setup target (informational)
setup:
	@echo "Setup the build: `date`, starting..."
	@echo "The compiler is $(CC), version $(CC_VERSION)"
	@echo "The flags used for compilation are: $(CFLAGS)"

# Phony targets
.PHONY: all clean setup