# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# SDL2 flags
SDL2_CFLAGS = $(shell sdl2-config --cflags)
SDL2_LDFLAGS = $(shell sdl2-config --libs)

# Executable name
TARGET = doodoo

# Math library
LIBS = -lm

# Source files
SRCS = $(wildcard *.c) 

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET) git_commit

# Build the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(SDL2_LDFLAGS) $(LIBS) -o $(TARGET)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) $(SDL2_CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Git commit step after successful build
git_commit:
	git add .
	git commit -m "Build commit: $(shell date '+%Y-%m-%d %H:%M:%S')" || true

