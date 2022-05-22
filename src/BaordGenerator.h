#pragma once
#include <queue>
#include "Board.h"

namespace Sudoku
{
    class BoardGenerator
    {
        public:
            template<int BASE>
            static void Generate(std::queue<Board<BASE>*> &initQueue,  int count);
    };
} // namespace Sudoku


template<int BASE>
void Sudoku::BoardGenerator::Generate(std::queue<Board<BASE>*> &initQueue,  int count)
{
    while(initQueue.size() < count)
    {
        Sudoku::Board<BASE>* b = initQueue.front();
        initQueue.pop();
        Sudoku::Cell cell = b->EmptyCells[b->EmptyCellsCount - 1];
        uint16_t occupants = b->GetOccupants(cell);
        uint16_t candidate = Sudoku::Board<BASE>::NextCandidate(occupants);
        occupants ^= candidate;

        while(occupants <= b->CELL_COMPLETELY_OCCUPIED)
        {
            Sudoku::Board<BASE>* nextBoard = new Sudoku::Board<BASE>(*b);
            initQueue.push(nextBoard);
            if(initQueue.size() == count)
            {
                nextBoard->SetExtraOccupant(cell, occupants ^ candidate);
                break;
            }
            nextBoard->SetValue(cell, candidate);
            nextBoard->EmptyCellsCount--;
            candidate = Sudoku::Board<BASE>::NextCandidate(occupants);
            occupants ^= candidate;
        }
    }
}
