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

bool solveInner(short* puzzle, short* rows, short* cols, short* boxes, const Cell* emptyCells, int index);

void solve(const short* puzzle, short* solution)
{

    // ANALYZE
    short rows[9] = {0};
    short cols[9] = {0};
    short boxes[9] = {0};
    Cell emptyCells[9*9 - 17] = {}; // maximalni pocet neznamych bunek
    int emptyCellsCount = 0;

    for (int row = 0; row < 9; row++)
        for (int col = 0; col < 9; col++)
        {
            int box = (row / 3) * 3 + col / 3;
            if (puzzle[row*9 + col] !=0)
            {
                short value = 1 << puzzle[row*9 + col] - 1;
                rows[row] ^= value;
                cols[col] ^= value;
                boxes[box] ^= value;
            }
            else
            {
                emptyCells[emptyCellsCount++] = {row, col, box};
            }
        }
    memcpy(solution, puzzle, sizeof(short)*81);
    // END ANALYZE

    solveInner(solution, rows, cols, boxes, emptyCells, emptyCellsCount-1);
}

inline short getNextCandidate(short candidates)
{
    return ~candidates & -~candidates;
}

bool solveInner(short* puzzle, short* rows, short* cols, short* boxes, const Cell* emptyCells, int index)
{
    if (index < 0) return true;

    int rowInd = emptyCells[index].Row;
    int colInd = emptyCells[index].Coll;
    int boxInd = emptyCells[index].Box;
    short candidates = rows[rowInd] | cols[colInd] | boxes[boxInd];
    short nextCandidate = 0;

    
    while(candidates != (short)511)
    {
        nextCandidate = getNextCandidate(candidates);   
        candidates ^= nextCandidate;
        rows[rowInd] ^= nextCandidate;
        cols[colInd] ^= nextCandidate;
        boxes[boxInd] ^= nextCandidate;

        if (solveInner(puzzle, rows, cols, boxes, emptyCells, index - 1))
        {   
            puzzle[rowInd * 9 + colInd] = (short) __builtin_ffs(nextCandidate);
            return true;
        }
        rows[rowInd] ^= nextCandidate;
        cols[colInd] ^= nextCandidate;
        boxes[boxInd] ^= nextCandidate;
    }
    return false;
}


