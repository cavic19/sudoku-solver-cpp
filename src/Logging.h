#pragma once
#include "Board.h"
namespace Sudoku
{
    template<int BASE>
    void printBoardWithCandidates(const Board<BASE>* b);

    template<int BASE>
    void printBoard(const Board<BASE>* b);
    
    void printPuzzle(const int* puzzle, int width);
    bool assertPuzzles(const int* puzzle1, const int* puzzle2);
} // namespace Sudoku
