#include <iostream>
#include "Parser.h"
#include "Solver.h"
#include <string>
using namespace Sudoku;
using namespace std;
bool AssertPuzzles(const int* puzzle1, const int* puzzle2, string* errorMessage);

int main()
{
    string test = "2X1f6dXX0X94b7X36Xb7XX0XX8aXX2194X35aXX1eXX7680X08X9X7Xf1362a4X57X91Xc8aXeX523XdXX0Xd3768Xf1459XXX5a2XXbXX0XX16c34XdXX1e2XXcXfa05XXX4XfX792XdXe1XXX87b3XXc1eX6XXX1X4XX2cbX5X9X3XebXX1X593Xda0c8X13X0c4XXa2XXXXXbd9fe8XX5c47bX026XX2cXXX35680X9XaaXX69XbXXX3dXXX8;2a1f6de80594b7c36cb73504d8afe2194d35a291ebc7680f08e9b7cf1362a4d57f910c8a6e4523bdc20bd3768af1459e8e5a2f4b9d03716c346d591e27bc8fa056c34af07928dbe190a87b3d4c1ef652f1d4e82cb0569a37eb7216593fda0c841380c467a2e95dfbd9fe81a5c47b3026b72cfed35680194aa54690b2f13dce78";
    Parser parser(16);
    int puzzle[256];
    int expectedSollution[256];
    int actualSollution[256];
    parser.Parse(test, puzzle, expectedSollution);    
    Solver<4> solver(true);

    cout << "Solutions: " << solver.GetLastFoundSolutions() << endl;
    cout << "Found solutions?" << solver.WasSolutionFound() << endl;
    cout << endl;
    solver.Solve(puzzle, actualSollution);

    cout << "Solutions: " << solver.GetLastFoundSolutions() << endl;
    cout << "Found solutions?" << solver.WasSolutionFound() << endl;

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
                *errorMessage += to_string(puzzle1[i * 16 + j]) + ", ";
            }
            else
            {   
                *errorMessage += to_string(puzzle1[i * 16 + j]) + "[" + to_string(puzzle2[i * 16 + j]) + "], ";
                isSuccess = false;
            }
        }
        *errorMessage += '\n';
    }

    return isSuccess;
}