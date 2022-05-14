#include "SudokuTests.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include "../src/BacktrackingSolver.h"
#include "../src/Parser.h"

using namespace std;
using namespace Sudoku;

const int SUDOKU_BASE = 4;
const int SUDOKU_SIZE = SUDOKU_BASE * SUDOKU_BASE;
const int PUZZLES_BUFFER_SIZE = 500;
int **puzzles, **solutions, puzzleCount = 0;
void apendPuzzleAndSolutionsFromFiles(char** file_paths, int length);
void printTestResult(TestResult &t, bool printDetails = false);
void cleanUp();

int main(int argc, char **argv)
{
    puzzles = new int*[PUZZLES_BUFFER_SIZE];
    solutions = new int*[PUZZLES_BUFFER_SIZE];
    apendPuzzleAndSolutionsFromFiles(argv + 1, argc - 1);


    BacktrackingSolver<SUDOKU_BASE> solver;
    Tests<SUDOKU_BASE> tests(puzzles, solutions, puzzleCount, &solver);
    TestResult t = tests.Run();
    printTestResult(t);
    void cleanUp();
}

void apendPuzzleAndSolutionsFromFiles(char** file_paths, int length)
{
    Parser parser(SUDOKU_SIZE);
    for (int i = 0; i < length; i++)
    {
        string filePath(file_paths[i]);
        ifstream file(filePath);
        string line;
        while(getline(file, line))
        {
            int* puzzle = new int[256];
            int* solution = new int[256];
            parser.Parse(line, puzzle, solution);
            puzzles[puzzleCount] = puzzle;
            solutions[puzzleCount++] = solution;
        }
        file.close();
    }
}

void printTestResult(TestResult &t, bool printDetails)
{
    cout << "Tests: " << t.TestCount << endl;
    if (printDetails)
    {
        cout << "Times: " << endl;
        for (int i = 0; i < t.TestCount; i++)
        {
            cout << i << ": " << t.times[i] << "[ns]" << "\t" << (t.isSuccess[i] ? "OK" : "FAIL") << endl;
            if(!t.isSuccess[i])
            {
                cout << t.statusMessages[i] << endl;
            }
        }
    }
    if (t.Fails > 0)
        cout << "Fails: " << t.Fails << endl;
    cout << "Avg[ns]: " << t.GetAvgTimeInNs() << endl;
}

void cleanUp()
{
    for (int i = 0; i < puzzleCount; i++ )
    {
        delete[] puzzles[i];
    }
    delete[] puzzles;
}

