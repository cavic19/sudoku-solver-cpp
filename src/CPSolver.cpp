#include "CPSolver.h"
#include <cstring>
#include "Board.h"
#include "Logging.h"
// #define LOG

template<int BASE>
void Sudoku::CPSolver<BASE>::Solve(const int* puzzle, int* solution)
{
    board = new Board<BASE>(puzzle, solution);
    // ApplyStrattegy(&SolveByCombinationOfBothStrategies);
    ApplyStrattegy(&CPSolver<BASE>::SolveSinglesStrategy);
    // ApplyStrattegy(&SolveLoneRangersStrategy);
}

template<int BASE>
void Sudoku::CPSolver<BASE>::ApplyStrattegy(bool (CPSolver<BASE>::*strategy) (Cell&))
{
    bool hasChanged = false;
    do
    {
        hasChanged = false;
        auto it = board->EmptyCells.begin();
        while (it != board->EmptyCells.end())
        {    
            if((this->*(strategy))(*it))
            {
                hasChanged = true;
                it = board->EmptyCells.erase(it);
            }
            else
            {
                ++it;
            }
        }
        #ifdef LOG
        printBoardWithCandidates<BASE>(board);
        #endif
    } while (hasChanged);
}



template<int BASE>
bool Sudoku::CPSolver<BASE>::SolveSinglesStrategy(Cell &cell)
{
    uint16_t occupants = board->GetOccupants(cell);
    if (HasLastCandidate(occupants))
    {
        uint16_t value = GetNextCandidate(occupants);
        board->SetValue(cell, value);
        return true;
    }
    return false;
}



template<int BASE>
bool Sudoku::CPSolver<BASE>::SolveLoneRangersStrategy(Cell &cell)
{
    uint16_t uniqueOccupantsInRow, uniqueOccupantsInCol, uniqueOccupantsInBox;
    uniqueOccupantsInRow = uniqueOccupantsInCol = uniqueOccupantsInBox = ~(board->GetOccupants(cell));
    for (Cell peer : board->EmptyCells)
    {
        if (peer == cell)
        {
            continue;
        }
        uint16_t peerOccupants = board->GetOccupants(peer);
        if(peer.RowInd == cell.RowInd)
        {
            uniqueOccupantsInRow &= peerOccupants;
        }
        if(peer.ColInd == cell.ColInd)
        {
            uniqueOccupantsInCol &= peerOccupants;
        }
        if(peer.BoxInd == cell.BoxInd)
        {
            uniqueOccupantsInBox &= peerOccupants;
        }
    }

    if(__builtin_popcount(uniqueOccupantsInRow) == 1)
    {
        board->SetValue(cell, uniqueOccupantsInRow);
        return true;
    }

    if(__builtin_popcount(uniqueOccupantsInCol) == 1)
    {
        board->SetValue(cell, uniqueOccupantsInCol);
        return true;
    }

    if(__builtin_popcount(uniqueOccupantsInBox) == 1)
    {
        board->SetValue(cell, uniqueOccupantsInBox);
        return true;
    }

    return false;
}


template<int BASE>
bool Sudoku::CPSolver<BASE>::SolveByCombinationOfBothStrategies(Cell &cell)
{
    return SolveSinglesStrategy(cell) || SolveLoneRangersStrategy(cell);
}





template class Sudoku::CPSolver<2>;
template class Sudoku::CPSolver<3>;
template class Sudoku::CPSolver<4>;