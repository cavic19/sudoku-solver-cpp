Test.exe: Tests.o SudokuTests.o SudokuSolver.o
	g++ Tests.o SudokuTests.o SudokuSolver.o -o Test.exe

Tests.o: Tests.cpp
	g++ -c Tests.cpp

SudokuTests.o: SudokuTests.cpp SudokuTests.h
	g++ -c SudokuTests.cpp

SudokuSolver.o: ..\src\SudokuSolver.cpp ..\src\SudokuSolver.h
	g++ -c ..\src\SudokuSolver.cpp

clean:
	rm Test.exe *.o