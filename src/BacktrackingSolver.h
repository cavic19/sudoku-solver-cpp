#pragma once
#include "Board.h"
#include <cstring>

namespace Sudoku
{
    // Solver for sudoku BASE^2 X BASE^2 up to BASE^2 == 16
    // The appropriate sudoku values mst follow 0, 1, 2, ..., BASE^2 - 1
    template<int BASE>
    class BacktrackingSolver
    {
        public:
            BacktrackingSolver(Board<BASE> &board);
            bool Solve();
   
        private:
            Board<BASE> &board;     
            bool Backtrack(int emptyCellIndex);

    };

    template class BacktrackingSolver<3>;
    template class BacktrackingSolver<4>;
}