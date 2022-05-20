#include <iostream>
#include "Parser.h"
#include "Logging.h"
#include "BacktrackingSolver.h"
#include <string>

const int BASE = 3;
const int WIDTH = BASE * BASE;
const int CELL_COUNT = WIDTH * WIDTH;

int puzzle[CELL_COUNT];
int actualSolution[CELL_COUNT];

void InitPuzzles(std::string puzzleLine, bool withSolution);

int main()
{
    InitPuzzles(
        "4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......;417369825632158947958724316825437169791586432346912758289643571573291684164875293", 
        true);
    Sudoku::Board<BASE> board(puzzle);
    Sudoku::BacktrackingSolver<BASE> solver(board);
    solver.Solve();
    Sudoku::assertPuzzles(board, actualSolution);
    return 0;
}


void InitPuzzles(std::string puzzleLine, bool withSolution = false)
{
    Sudoku::Parser p(WIDTH);
    if (withSolution)
    {
        p.Parse(puzzleLine, puzzle, actualSolution);
    }
    else
    {
        p.Parse(puzzleLine, puzzle);
    }
}