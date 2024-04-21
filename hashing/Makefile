# Compiler settings
CXX = g++
NVCC = nvcc
CXXFLAGS = -std=c++11
NVCCFLAGS = -std=c++11

# Name of the target executable
TARGET = main
# Path to the target executable
TARGET_PATH = build/$(TARGET)

# Directory for source files
SRC_DIR = src
# Directory for build outputs
BUILD_DIR = build

# Source files
SRC = $(wildcard $(SRC_DIR)/*.cpp)
CU_SRC = $(wildcard $(SRC_DIR)/*.cu)

# Object files
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o) $(CU_SRC:$(SRC_DIR)/%.cu=$(BUILD_DIR)/%.o)

# Header files
HEADERS = $(wildcard $(SRC_DIR)/*.h)

# Default rule
all: $(TARGET_PATH)

# Rule to create the build directory
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Rule to link the program
$(TARGET_PATH): $(OBJ)
	$(NVCC) $(NVCCFLAGS) -o $@ $(OBJ)

# Rule to compile C++ source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile CUDA source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cu $(HEADERS)
	@mkdir -p $(@D)
	$(NVCC) $(NVCCFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
