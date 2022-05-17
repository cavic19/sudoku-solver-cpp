#pragma once
#include "Board.h"
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

            inline bool HasLastCandidate(uint16_t occupants);
            inline uint16_t GetNextCandidate(uint16_t occupants);

        public:
            void Solve(const int* puzzle, int* solution);
    };
} // namespace Sudoku
