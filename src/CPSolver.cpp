#include <vector>

struct Cell
{
    int RowInd;
    int ColInd;
    int BoxInd;

    friend bool operator==(const Cell& cell1, const Cell& cell2)
    {
        return cell1.RowInd == cell2.RowInd && cell1.ColInd == cell2.ColInd;
    }
    friend bool operator!=(const Cell& cell1, const Cell& cell2)
    {
        return !(cell1 == cell2);
    }
};


const int BASE = 3;
constexpr int DIM = BASE * BASE;
short rowOccupants[DIM] = {0};
short colOccupants[DIM] = {0};
short boxOccupants[DIM] = {0};

std::vector<Cell> emptyCells;
std::vector<Cell*> rows[DIM];
std::vector<Cell*> cols[DIM];
std::vector<Cell*> boxes[DIM];


int puzzle[DIM * DIM];

void init()
{
    for (int row = 0; row < DIM; row++)
        for (int col = 0; col < DIM; col++)
        {
            int box = (row / BASE) * BASE + col / BASE;
            if (puzzle[row * DIM + col] >= 0)
            {
                short value = 1 << puzzle[row * DIM + col];
                rowOccupants[row] ^= value;
                colOccupants[col] ^= value;
                boxOccupants[box] ^= value;
            }
            else
            {
                emptyCells.push_back({row, col, box});
                rows[row].push_back(&emptyCells.back());
                cols[col].push_back(&emptyCells.back());
                boxes[box].push_back(&emptyCells.back());
            }
        }      
}


inline short getOccupants(Cell &cell)
{
    return rowOccupants[cell.RowInd] | colOccupants[cell.ColInd] | boxOccupants[cell.BoxInd];
}

inline short countCandidates(short occupants)
{
    return DIM - __builtin_popcount(occupants);
}

inline short getCandidate(short occupants)
{
    return ~occupants & -~occupants;
}

bool propagate()
{
    bool changed = false;

    do // (1) Eliminate singlets
    {
        bool changed = false;
        for (Cell c : emptyCells)
        {
            short occupants = getOccupants(c);
            if (countCandidates(occupants) == 1)
            {
                short value = getCandidate(occupants);
                rowOccupants[c.RowInd] ^= value;
                colOccupants[c.ColInd] ^= value;
                boxOccupants[c.BoxInd] ^= value;
                puzzle[c.RowInd * DIM + c.ColInd] =  __builtin_ffs(value) - 1;
                changed = true;    
            }
        }
    }
    while(changed);




    do // (2) 
    { 
        for (Cell cell : emptyCells)
        {
            changed = false;
            // Checks peers in row
            short cellOccupants = getOccupants(cell);
            for (Cell* rowPeerCell : rows[cell.RowInd])
            {
                if(*rowPeerCell == cell) continue;
                cellOccupants |= getOccupants(*rowPeerCell);
            }

            if(countCandidates(cellOccupants) == 1)
            {
                short newValue = getCandidate(cellOccupants);
                rowOccupants[cell.RowInd] ^= newValue;
                colOccupants[cell.ColInd] ^= newValue;
                boxOccupants[cell.BoxInd] ^= newValue;
                puzzle[cell.RowInd * DIM + cell.ColInd] = __builtin_ffs(newValue) - 1;
                changed = true;
                continue;
            }


            // Checks peers in column
            short cellOccupants = getOccupants(cell);
            for (Cell* colPeerCell : cols[cell.ColInd])
            {
                if(*colPeerCell == cell) continue;
                cellOccupants |= getOccupants(*colPeerCell);
            }

            if(countCandidates(cellOccupants) == 1)
            {
                short newValue = getCandidate(cellOccupants);
                rowOccupants[cell.RowInd] ^= newValue;
                colOccupants[cell.ColInd] ^= newValue;
                boxOccupants[cell.BoxInd] ^= newValue;
                puzzle[cell.RowInd * DIM + cell.ColInd] = __builtin_ffs(newValue) - 1;
                changed = true;
                continue;
            }

            // Checks peers in boxes
            short cellOccupants = getOccupants(cell);
            for (Cell* boxPeerCell : boxes[cell.BoxInd])
            {
                if(*boxPeerCell == cell) continue;
                cellOccupants |= getOccupants(*boxPeerCell);
            }

            if(countCandidates(cellOccupants) == 1)
            {
                short newValue = getCandidate(cellOccupants);
                rowOccupants[cell.RowInd] ^= newValue;
                colOccupants[cell.ColInd] ^= newValue;
                boxOccupants[cell.BoxInd] ^= newValue;
                puzzle[cell.RowInd * DIM + cell.ColInd] = __builtin_ffs(newValue) - 1;
                changed = true;
                continue;
            }
        }
    } 
    while(changed);
    
}
