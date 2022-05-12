#include "SudokuSolver.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    char input[257] = "d8a1cX39X7XeX0X2f2XXbXX6XX0cX17537XXXXX42X51aX9c0bc5X2f79XXXeXXX90bXfXXceXXX65XX1c3fX98XXX6524b7aXXXXXXb7X8XfXX346d7a3X5cfX01XX87923XXXX4XXfXa6051fXX4c806abXdXXbd846a50129XXeXXXa0c7X92Xe3X4X81c47bX86Xa0dX93XXXf9X4713b5e6XXdaeXXX2cXdX9XX8Xfb2XXdXbeaXcX8X6X4";
    int puzzle[256];
    int sollution[256];
    for (int i = 0; i <256; i++)
    {
        if (input[i] == 'X')
        {
           puzzle[i] = -1; 
        }
        else
        {
            puzzle[i] = (input[i] >= 'a') ? (input[i] - 'a' + 10) : (input[i] - '0');
        }
    }
    
    solve(puzzle, sollution);
    
    for (int row = 0; row < 16; row++)
    {
        for (int col = 0; col < 16; col++)
        {
                switch (sollution[row * 16 + col])
                {
                case 10:
                    cout << "a";
                    break;
                case 11:
                    cout << "b";
                    break;
                case 12:
                    cout << "c";
                    break;
                case 13:
                    cout << "d";
                    break;
                case 14:
                    cout << "e";
                    break;
                case 15:
                    cout << "f";
                    break;
                default:
                    cout << sollution[row * 16 + col];
                    break;
                }
        }
        cout << endl;
    }

    return 0;
}