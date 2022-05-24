CC=g++
BUILD_DIR = .\build
SRC_BUILD_DIR = ..\src\build
SRC_OBJ = $(SRC_BUILD_DIR)/BacktrackingSolver.o $(SRC_BUILD_DIR)/Board.o $(SRC_BUILD_DIR)/IndexedQueue.o $(SRC_BUILD_DIR)/Parser.o $(SRC_BUILD_DIR)/Logging.o
MSPI_LIB = "${MSMPI_LIB64}msmpi.lib"

p: test_parallel.cpp
	$(CC) test_parallel.cpp $(SRC_OBJ) $(MSPI_LIB) -o $(BUILD_DIR)/test_parallel.exe

s: test_sequential.cpp
	$(CC) test_sequential.cpp $(SRC_OBJ) -o $(BUILD_DIR)/test_sequential.exe

clean:
	del $(BUILD_DIR)\test_parallel.exe $(BUILD_DIR)\test_sequential.exe $(BUILD_DIR)\*.o