#pragma once
#include <queue>
#include "Board.h"
#include "IndexedQueue.h"

namespace Sudoku
{
    class BoardGenerator
    {
        public:
            template<int BASE>
            static void Generate(IndexedQueue<Board<BASE>*, 100> &initQueue,  int count);
    };
} // namespace Sudoku


template<int BASE>
void Sudoku::BoardGenerator::Generate(IndexedQueue<Board<BASE>*, 100> &initQueue,  int count)
{
    while(initQueue.Size() < count)
    {
        Sudoku::Board<BASE>* b = initQueue.Dequeue();
        Sudoku::Cell cell = b->EmptyCells[b->EmptyCellsCount - 1];
        uint16_t occupants = b->GetOccupants(cell);
        uint16_t candidate = Sudoku::Board<BASE>::NextCandidate(occupants);
        occupants ^= candidate;

        while(occupants <= b->CELL_COMPLETELY_OCCUPIED)
        {
            Sudoku::Board<BASE>* nextBoard = new Sudoku::Board<BASE>(*b);
            initQueue.Enqueue(nextBoard);
            if(initQueue.Size() == count)
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
