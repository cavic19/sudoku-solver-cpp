.\build\Test.exe: .\build\Tests.o .\build\SudokuTests.o .\build\Solver.o .\build\Parser.o
	g++ .\build\Tests.o .\build\SudokuTests.o .\build\Solver.o .\build\Parser.o -o .\build\Test.exe

.\build\Tests.o: Tests.cpp
	g++ -c Tests.cpp -o .\build\Tests.o

.\build\SudokuTests.o: SudokuTests.cpp SudokuTests.h
	g++ -c SudokuTests.cpp -o .\build\SudokuTests.o

.\build\Solver.o: ..\src\Solver.cpp ..\src\Solver.h
	g++ -c ..\src\Solver.cpp -o .\build\Solver.o

.\build\Parser.o: ..\src\Parser.cpp ..\src\Parser.h
	g++ -c ..\src\Parser.cpp -o .\build\Parser.o

clean:
	del .\build\Test.exe .\build\*.o