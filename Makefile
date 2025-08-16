# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinclude -g

# Source code files (in C)
SRCS = src/main.c data/generate_sensor_inputs.c

# Corresponding object files (placed in /build)
OBJS = $(SRCS:%.c=build/%.o)

# Executable name
EXEC = logger

# Final target: link all object files into the executable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@

# Object files rule: compile in /build
build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files and executable
clean:
	rm -rf build $(EXEC)
