#pragma once
#include "Board.h"
#include <cstring>


namespace Sudoku
{
    template<int BASE>
    class CPSolver
    {
        private:
            bool ApplyStrattegy(bool (Sudoku::CPSolver<BASE>::*strategy)(Cell&));
            bool SolveSinglesStrategy(Cell &cell);
            bool SolveLoneRangersStrategy(Cell &cell);
            bool SolveByCombinationOfBothStrategies(Cell &cell);

            inline bool HasLastCandidate(uint16_t occupants)
            {
                return board->WIDTH - 1 == __builtin_popcount(occupants);
            }

            inline uint16_t GetNextCandidate(uint16_t occupants)
            {
                return ~occupants & -~occupants;
            }

        public:
            Board<BASE>* board;
            bool Solve(const int* puzzle, int* solution);
            bool Solve(const int* puzzle, Board<BASE>* board);
    };
} // namespace Sudoku
