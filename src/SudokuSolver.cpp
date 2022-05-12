# include <cstring>
#include <cstdint>
struct Cell
{
    int Row;
    int Coll;
    int Box; 
};

struct CellStack
{
    int Count;
    Cell* Cells;
    Cell* Pop()
    {
        return &Cells[Count--]; 
    }
    void Push(Cell cell)
    {
        Cells[++Count] = cell;
    }
};

bool solveInner(int* puzzle, short* rows, short* cols, short* boxes, const Cell* emptyCells, int index);

void solve(const int* puzzle, int* solution)
{

    // ANALYZE
    short rows[16] = {0};
    short cols[16] = {0};
    short boxes[16] = {0};
    Cell emptyCells[16*16 - 55] = {}; // 55 as the smalles number of clues for 16x16 sudoku
    int emptyCellsCount = 0;

    for (int row = 0; row < 16; row++)
        for (int col = 0; col < 16; col++)
        {
            int box = (row / 4) * 4 + col / 4;
            if (puzzle[row*16 + col] != -1)
            {
                short value = 1 << puzzle[row*16 + col];
                rows[row] ^= value;
                cols[col] ^= value;
                boxes[box] ^= value;
            }
            else
            {
                emptyCells[emptyCellsCount++] = {row, col, box};
            }
        }
    memcpy(solution, puzzle, sizeof(int)*256);
    // END ANALYZE

    solveInner(solution, rows, cols, boxes, emptyCells, emptyCellsCount-1);
}

inline short getNextCandidate(short candidates)
{
    return ~candidates & -~candidates;
}

bool solveInner(int* puzzle, short* rows, short* cols, short* boxes, const Cell* emptyCells, int index)
{
    if (index < 0) return true;

    int rowInd = emptyCells[index].Row;
    int colInd = emptyCells[index].Coll;
    int boxInd = emptyCells[index].Box;
    short candidates = rows[rowInd] | cols[colInd] | boxes[boxInd];
    short nextCandidate = 0;

    
    while(candidates != (short)65535)
    {
        nextCandidate = getNextCandidate(candidates);   
        candidates ^= nextCandidate;
        rows[rowInd] ^= nextCandidate;
        cols[colInd] ^= nextCandidate;
        boxes[boxInd] ^= nextCandidate;

        if (solveInner(puzzle, rows, cols, boxes, emptyCells, index - 1))
        {   
            puzzle[rowInd * 16 + colInd] = __builtin_ffs(nextCandidate) - 1;
            return true;
        }
        rows[rowInd] ^= nextCandidate;
        cols[colInd] ^= nextCandidate;
        boxes[boxInd] ^= nextCandidate;
    }
    return false;
}


