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
        "3.6.7...........518.........1.4.5...7.....6.....2......2.....4.....8.3.....5.....", // extra hard puzzle ~11s
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