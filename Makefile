# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Source files
SRCS = main.cpp file1.cpp file2.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = myprogram

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
    $(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files from source files
%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
    rm -f $(OBJS) $(TARGET)
