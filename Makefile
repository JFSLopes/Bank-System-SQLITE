# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Directories
SRC_DIR = source
BUILD_DIR = build

# Output binary
TARGET = $(BUILD_DIR)/program

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Main target
all: $(TARGET)

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files into binary
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lsqlite3

# Clean build directory
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
