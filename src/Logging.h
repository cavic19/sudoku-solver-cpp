#pragma once
#include "Board.h"
namespace Sudoku
{
    template<int BASE>
    void printBoardWithCandidates(const Board<BASE>* b);

    void printCandidates(uint16_t candidates, int width);


    template<int BASE>
    void printPuzzle(const Board<BASE>* b);  
    void printPuzzle(const int* puzzle, int width);

    
    template<int BASE>
    bool assertPuzzles(const Board<BASE> &board, const int* expectedSolution);
    bool assertPuzzles(const int* puzzle1, const int* puzzle2, int width);
} // namespace Sudoku
