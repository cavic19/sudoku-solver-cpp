#include "BacktrackingSolver.h"
#include <cstring>

template<int BASE>
Sudoku::BacktrackingSolver<BASE>::BacktrackingSolver(Board<BASE> &board) : board(board)
{ 
  
}

template<int BASE>
bool Sudoku::BacktrackingSolver<BASE>::Solve()
{
    return Backtrack(board.EmptyCellsCount - 1);
}

template<int BASE>
bool Sudoku::BacktrackingSolver<BASE>::Backtrack(int emptyCellIndex)
{
    if (emptyCellIndex < 0) return true;

    Cell cell = board.EmptyCells[emptyCellIndex];
    uint16_t occupants = board.GetOccupants(cell);
    short nextCandidate = 0;

    while(occupants != board.CELL_COMPLETELY_OCCUPIED)
    {
        nextCandidate = Board<BASE>::NextCandidate(occupants);
        occupants ^= nextCandidate;
        board.Eliminate(cell, nextCandidate);

        if (Backtrack(emptyCellIndex - 1))
        {   
            board.SetValueWithoutElimination(cell, nextCandidate);
            return true;
        }
        board.Eliminate(cell, nextCandidate);
    }
    return false;  
}


