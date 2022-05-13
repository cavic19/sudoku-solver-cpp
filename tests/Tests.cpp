#include "SudokuTests.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include "../src/Solver.h"
#include "../src/Parser.h"

using namespace std;
using namespace Sudoku;
void printPuzzle(const int* puzzle);
int main(int argc, char **argv)
{
    int** puzzles = new int*[500];
    int** sollutions = new int*[500];
    int puzzleCount = 0;
    Parser parser(16);
    for (int i = 1; i < argc; i++)
    {
        string filePath(argv[i]);
        ifstream file(filePath);
        string line;
        while(getline(file, line))
        {
            int* puzzle = new int[256];
            int* sollution = new int[256];
            parser.Parse(line, puzzle, sollution);
            puzzles[puzzleCount] = puzzle;
            sollutions[puzzleCount++] = sollution;
        }
        file.close();
    }


    Solver<4> solver(true);
    Tests<4> tests(puzzles, sollutions, puzzleCount, &solver);
    TestResult t = tests.Run();
    cout << "Tests: " << t.TestCount << endl;
    cout << "Fails: " << t.Fails << endl;
    cout << "Times: " << endl;
    for (int i = 0; i < t.TestCount; i++)
    {
        if (t.numberOfSolutions[i] == 1)
            cout << i + 1 << ": " << t.times[i] << "[ns]" << "\t" << (t.isSuccess[i] ? "OK" : "FAIL") << ", n=" << t.numberOfSolutions[i] << endl;
    }
    cout << "Average: " << t.GetAvgTimeInNs() << "[ns]" << endl;
    

    for (int i = 0; i < puzzleCount; i++ )
    {
        delete[] puzzles[i];
    }
    delete[] puzzles;
}


