#include <chrono>
#include <string>
#include <iostream>
#include "..\src\Parser.h"
#include "..\src\Logging.h"
#include "..\src\BacktrackingSolver.h"
#include "..\src\Board.h"

const int BASE = 3;
const int WIDTH = BASE * BASE;
const int CELL_COUNT = WIDTH * WIDTH;

int puzzle[CELL_COUNT];
int actualSolution[CELL_COUNT];

void InitPuzzles(std::string puzzleLine, bool withSolution);

int main()
{
    InitPuzzles(
        ".4..5..67...1...4....2.....1..8..3........2...6...........4..5.3.....8..2........", 
        false);

    Sudoku::Board<BASE> board(puzzle);
    Sudoku::BacktrackingSolver<BASE> solver(board);
    auto start = std::chrono::steady_clock::now();
    solver.Solve();
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
    std::cout << "Elapsed time: " << elapsed << "ms\n";

    Sudoku::printPuzzle(&board);
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