#include "BacktrackingSolver.h"
#include <cstring>

template<int BASE>
void Sudoku::BacktrackingSolver<BASE>::Analyze(const int* puzzle, int* sollution)
{
    for (int row = 0; row < WIDTH; row++)
        for (int col = 0; col < WIDTH; col++)
        {
            int box = (row / BASE) * BASE + col / BASE;
            if (puzzle[row * WIDTH + col] != -1)
            {
                short value = 1 << puzzle[row * WIDTH + col];
                rows[row] ^= value;
                cols[col] ^= value;
                boxes[box] ^= value;
            }
            else
            {
                emptyCells[emptyCellsCount++] = {row, col, box};
            }
        }
    memcpy(sollution, puzzle, sizeof(int) * CELL_COUNT);
}

template<int BASE>
bool Sudoku::BacktrackingSolver<BASE>::Backtrack(int* puzzle, int emptyCellIndex)
{
    if (emptyCellIndex < 0) return true;
    
    int rowInd = emptyCells[emptyCellIndex].Row;
    int colInd = emptyCells[emptyCellIndex].Coll;
    int boxInd = emptyCells[emptyCellIndex].Box;

    short candidates = rows[rowInd] | cols[colInd] | boxes[boxInd];
    short nextCandidate = 0;

    while(candidates != NO_CANDIDATES)
    {
        nextCandidate = NextCandidate(candidates);
        candidates ^= nextCandidate;
        rows[rowInd] ^= nextCandidate;
        cols[colInd] ^= nextCandidate;
        boxes[boxInd] ^= nextCandidate;
        if (Backtrack(puzzle, emptyCellIndex - 1))
        {   
            puzzle[rowInd * WIDTH + colInd] = __builtin_ffs(nextCandidate) - 1;
            return true;
        }
        rows[rowInd] ^= nextCandidate;
        cols[colInd] ^= nextCandidate;
        boxes[boxInd] ^= nextCandidate;
    }
    return false;  
}

template<int BASE>
void Sudoku::BacktrackingSolver<BASE>::Solve(const int* puzzle, int* sollution)
{
    emptyCellsCount = 0;
    for (int i = 0; i < WIDTH; i++)
    {
        rows[i] = 0;
        cols[i] = 0;
        boxes[i] = 0;
    }
    Analyze(puzzle, sollution);
    Backtrack(sollution, emptyCellsCount - 1);
}

template<int BASE>
inline short Sudoku::BacktrackingSolver<BASE>::NextCandidate(short candidates)
{
    return ~candidates & -~candidates;
}
