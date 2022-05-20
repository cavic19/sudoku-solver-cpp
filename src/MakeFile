CC=g++
BUILD_DIR=.\build
TARGET=example
OBJ := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(wildcard *.cpp))

$(BUILD_DIR)/$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/%.o: %.cpp
	$(CC) -c $< -o $@

clean:
	del $(BUILD_DIR)\$(TARGET).exe $(BUILD_DIR)\*.o
