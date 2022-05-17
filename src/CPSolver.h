#pragma once
#include "Board.h"
#include <cstring>


namespace Sudoku
{
    template<int BASE>
    class CPSolver
    {
        private:
            Board<BASE>* board;
            void ApplyStrattegy(bool (Sudoku::CPSolver<BASE>::*strategy)(Cell&));
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
            void Solve(const int* puzzle, int* solution);
    };
} // namespace Sudoku
