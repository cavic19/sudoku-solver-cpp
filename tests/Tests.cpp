#include "SudokuTests.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

void extractPuzzleAndsolution(const string line, short* puzzle, short* solution);
void printPuzzle(const short* puzzle);
int main(int argc, char **argv)
{
    short** puzzles = new short*[500];
    short** sollutions = new short*[500];
    int puzzleCount = 0;

    for (int i = 1; i < argc; i++)
    {
        string filePath(argv[i]);
        ifstream file(filePath);
        string line;
        while(getline(file, line))
        {
            short puzzle[81];
            short sollution[81];
            extractPuzzleAndsolution(line, puzzle, sollution);
            puzzles[puzzleCount] = puzzle;
            sollutions[puzzleCount++] = sollution;
        }
        file.close();
    }
    SudokuTests sudokuTests(puzzles, sollutions, puzzleCount);
    TestResult t = *sudokuTests.Run();
    cout << "Tests: " << t.TestCount << endl;
    cout << "Fails: " << t.Fails << endl;
    cout << "Times: " << endl;
    for (int i = 0; i < t.TestCount; i++)
    {
        cout << i << ": " << t.times[i] << "[ns]" << endl;
    }
    cout << "Average: " << t.GetAvgTimeInNs() << "[ns]" << endl;
    
}


void extractPuzzleAndsolution(const string line, short* puzzle, short* solution)
{
    string puzzleText = line.substr(0, line.find(";")) + "\0";
    assert(puzzleText.length() == 81);
    for (int i = 0; i < puzzleText.length(); i++)
        puzzle[i] = puzzleText[i] - '0';
    
    string solutionText = line.substr(line.find(";")+1, line.length());
    assert(solutionText.length() == 81);
    for (int i = 0; i < solutionText.length(); i++)
        solution[i] = solutionText[i] - '0';
}

void printPuzzle(const short* puzzle)
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            cout << puzzle[row * 9 + col];
        }
        cout << endl;
    }   
}

