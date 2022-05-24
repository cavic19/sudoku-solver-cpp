CC=g++
BUILD_DIR = .\build
MSPI_LIB = "${MSMPI_LIB64}msmpi.lib"
TARGET=example
OBJ := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(wildcard *.cpp))

o: $(OBJ)

$(BUILD_DIR)/$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(MSPI_LIB) -o $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/%.o: %.cpp
	$(CC) -c $< -o $@

clean:
	del $(BUILD_DIR)\$(TARGET).exe $(BUILD_DIR)\*.o

