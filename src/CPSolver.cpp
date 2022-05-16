#include <vector>
#include <cstring>
#include <iostream>
void logStatus();
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


int* puzzle;

void printPuzzle()
{
    for (int row = 0; row < DIM; row++)
    {
        for (int col = 0; col < DIM; col++)
        {
            std::cout << puzzle[row * DIM + col]  << " ";
        }
        std::cout << std::endl;
    }
    
}

void init()
{
    for (int row = 0; row < DIM; row++)
        for (int col = 0; col < DIM; col++)
        {
            int box = (row / BASE) * BASE + col / BASE;
            if (puzzle[row * DIM + col] != -1)
            {
                short value = 1 << puzzle[row * DIM + col] - 1;
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

void logCell(Cell c)
{
    std::cout << "Cell(" << c.RowInd << "," << c.ColInd <<"," << c.BoxInd << ")" << std::endl;
}

void propagate()
{
    bool changed = false;

    do // (1) Eliminate singlets
    {
        changed = false;
        auto it = emptyCells.begin();
        while(it != emptyCells.end())
        {
            auto c = *it;
            std::cout << "Rule 1" << std::endl;
            logCell(c);
            short occupants = getOccupants(c);
            if (countCandidates(occupants) == 1)
            {
                short value = getCandidate(occupants);
                rowOccupants[c.RowInd] ^= value;
                colOccupants[c.ColInd] ^= value;
                boxOccupants[c.BoxInd] ^= value;
                puzzle[c.RowInd * DIM + c.ColInd] =  __builtin_ffs(value);
                changed = true;
                it = emptyCells.erase(it);    
            }
            else
            {
                ++it;
            }
        }
            std::cout << "First round end" << std::endl;
    }
    while(changed);


    logStatus();

    do // (2) 
    { 
        auto it = emptyCells.begin();
        while(it != emptyCells.end())
        {
            Cell cell = *it;
            std::cout << "Rule 2" << std::endl;
            logCell(cell);
            changed = false;
            // Checks peers in row
            short cellOccupants = getOccupants(*it);
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
                puzzle[cell.RowInd * DIM + cell.ColInd] = __builtin_ffs(newValue);
                changed = true;
                it = emptyCells.erase(it);
                continue;
            }


            // Checks peers in column
            cellOccupants = getOccupants(cell);
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
                it = emptyCells.erase(it);
                continue;
            }

            // Checks peers in boxes
            cellOccupants = getOccupants(cell);
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
                it = emptyCells.erase(it);
                continue;
            }
            ++it;
        }
    } 
    while(changed);
    
}


void solve(const int* puzzleee, int* solution)
{
    std::memcpy(solution, puzzleee, sizeof(int) * 81);
    puzzle = solution;


    init();

    logStatus();

    propagate();
}


void logStatus()
{
    for (int row = 0; row < DIM; row++)
    {
        for (int col = 0; col < DIM; col++)
        {
            if(puzzle[row * 9 + col] != -1)
            {
                std::cout << puzzle[row * 9 + col] << ",";
                continue;
            }
            int box = (row / BASE) * BASE + col / BASE;
            Cell c = {row, col, box};
            auto occupants = getOccupants(c);
            short candiates = 511 ^ occupants;
            for (int i = 0; i < DIM; i++)
            {
                if(candiates & (1 << i))
                {
                    std::cout << i + 1;
                }
            }
            std::cout << ",";
            
        }
        std::cout << std::endl;
    }
    
}