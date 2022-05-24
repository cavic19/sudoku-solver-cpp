CC=g++
BUILD_DIR = .\build
SRC_BUILD_DIR = ..\src\build
SRC_OBJ = $(SRC_BUILD_DIR)/BacktrackingSolver.o $(SRC_BUILD_DIR)/Board.o $(SRC_BUILD_DIR)/IndexedQueue.o $(SRC_BUILD_DIR)/Parser.o $(SRC_BUILD_DIR)/Logging.o
MSPI_LIB = "${MSMPI_LIB64}msmpi.lib"

p: $(BUILD_DIR)/test_parallel.o
	$(CC) $(SRC_OBJ) $(BUILD_DIR)/test_parallel.o $(MSPI_LIB) -o $(BUILD_DIR)/test_parallel.exe

$(BUILD_DIR)/test_parallel.o: test_parallel.cpp
	$(CC) -c test_parallel.cpp -o $(BUILD_DIR)/test_parallel.o 

s: $(BUILD_DIR)/test_sequential.o
	$(CC) $(SRC_OBJ) $(BUILD_DIR)/test_sequential.o -o $(BUILD_DIR)/test_sequential.exe

$(BUILD_DIR)/test_sequential.o: test_sequential.cpp
	$(CC) -c test_sequential.cpp -o $(BUILD_DIR)/test_sequential.o

clean:
	del $(BUILD_DIR)\test_parallel.exe $(BUILD_DIR)\test_sequential.exe $(BUILD_DIR)\*.o