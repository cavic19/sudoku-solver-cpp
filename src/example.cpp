#include <iostream>
#include "Parser.h"
#include <string>
using namespace Sudoku;
using namespace std;
bool AssertPuzzles(const int* puzzle1, const int* puzzle2, string* errorMessage);
void solve(const int*, int*);
void printPuzzle(const int* puzzle);

int main()
{
    string easyPuzzle = "..3.2.6..9..3.5..1..18.64....81.29..7.......8..67.82....26.95..8..2.3..9..5.1.3..;483921657967345821251876493548132976729564138136798245372689514814253769695417382";
    Parser parser(9, ';','.', -1);
    int puzzle[256];
    int expectedSollution[256];
    int actualSollution[256];
    parser.Parse(easyPuzzle, puzzle, expectedSollution);    
    printPuzzle(puzzle);


    solve(puzzle, actualSollution);
    string errorMessage = "";
    
    
    
    if (!AssertPuzzles(actualSollution, expectedSollution, &errorMessage))
    {
        cout << errorMessage;
    }
    return 0;
}

bool AssertPuzzles(const int* puzzle1, const int* puzzle2, string* errorMessage)
{
    bool isSuccess = true;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (puzzle1[i * 16 + j] == puzzle2[i * 16 + j])
            {
                *errorMessage  += to_string(puzzle1[i * 16 + j]) + ", ";
            }
            else
            {   
                *errorMessage  += to_string(puzzle1[i * 16 + j]) + "[" + to_string(puzzle2[i * 16 + j]) + "], ";
                isSuccess = false;
            }
        }
        *errorMessage += '\n';
    }


    return isSuccess;
}

void printPuzzle(const int* puzzle)
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            cout << puzzle[row * 9 + col] << ",";
        }
        cout << endl;
    }
    
}