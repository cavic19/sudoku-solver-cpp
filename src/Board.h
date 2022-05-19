#pragma once
#include <vector>
#include <cstring>
#include "stdint.h"

namespace Sudoku
{
    struct Cell
    {
        int RowInd;
        int ColInd;
        int BoxInd;

        friend bool operator==(const Cell& cell1, const Cell& cell2);
    };
    
    bool operator==(const Cell& cell1, const Cell& cell2);


    template<int BASE>
    class Board
    {
        public:
            static constexpr int WIDTH = BASE * BASE;
            static constexpr int CELL_COUNT = WIDTH * WIDTH;
            static constexpr uint16_t CELL_COMPLETELY_OCCUPIED = 65535 >> (sizeof(uint16_t) * 8 - WIDTH);

        private:   
            const int EMPTY_VALUE;
            
            uint16_t rowOccupants[WIDTH] = {0};
            uint16_t colOccupants[WIDTH] = {0};
            uint16_t boxOccupants[WIDTH] = {0};

            int* solution;
            void Init();
            void Eliminate(Cell& cell, uint16_t value);

        public:
            bool IsSolved() const;
            std::vector<Cell> EmptyCells;
            Board(const Board<BASE> &board, int* solution);
            Board(const int* puzzle, int* solution, int emptyValue = -1);
            void SetValue(Cell cell, uint16_t value);
            void SetValue(Cell cell, int value);
            int* GetSolution() const; 
            inline uint16_t GetOccupants(Cell cell) const
            {
                return rowOccupants[cell.RowInd] | colOccupants[cell.ColInd] | boxOccupants[cell.BoxInd];
            }

    };
} // namespace Sudoku
