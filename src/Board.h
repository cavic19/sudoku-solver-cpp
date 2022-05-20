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
            
            // TODO: Implement priority queue or something more efficient
            Cell EmptyCells[CELL_COUNT];
            int EmptyCellsCount = 0;

        public:
            Board(const int* puzzle, const int emptyValue = -1);
            Board(const Board<BASE> &);

            void SetValue(Cell cell, uint16_t value);
            void SetValueWithoutElimination(Cell cell, uint16_t value);
            void SetValue(Cell cell, int value);
            const int* GetSolution() const; 
            inline uint16_t GetOccupants(Cell cell) const
            {
                return rowOccupants[cell.RowInd] | colOccupants[cell.ColInd] | boxOccupants[cell.BoxInd];
            }
            inline void Eliminate(Cell cell, uint16_t value)
            {
                rowOccupants[cell.RowInd] ^= value;
                colOccupants[cell.ColInd] ^= value;
                boxOccupants[cell.BoxInd] ^= value;
            }

        private:   
            const int EMPTY_VALUE;
            int solution[CELL_COUNT];      
            uint16_t rowOccupants[WIDTH] = {0};
            uint16_t colOccupants[WIDTH] = {0};
            uint16_t boxOccupants[WIDTH] = {0};
            void Init();
    };
} // namespace Sudoku
