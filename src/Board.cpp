#include "Board.h"
#include <cstring>




bool Sudoku::operator==(const Sudoku::Cell& cell1, const Sudoku::Cell& cell2)
{
    return cell1.RowInd == cell2.RowInd && cell1.ColInd == cell2.ColInd;
}

template<int BASE>
bool Sudoku::Board<BASE>::IsSolved() const
{
    return EmptyCells.size() == 0;
}

template<int BASE>
void Sudoku::Board<BASE>::Init()
{
    for (int row = 0; row < WIDTH; row++)
        for (int col = 0; col < WIDTH; col++)
        {
            int box = (row / BASE) * BASE + col / BASE;
            if (solution[row * WIDTH + col] != EMPTY_VALUE)
            {
                SetValue({row, col, box}, solution[row * WIDTH + col]);
            }
            else
            {
                EmptyCells.push_back({row, col, box});
            }
        }
}

template<int BASE>
Sudoku::Board<BASE>::Board(const int* puzzle, int* solution, int emptyValue) : EMPTY_VALUE(emptyValue), solution(solution)
{
    EmptyCells.reserve(CELL_COUNT);
    std::memcpy(solution, puzzle, sizeof(int) * CELL_COUNT);
    Init();
}

template<int BASE>
Sudoku::Board<BASE>::Board(const Board<BASE> &b, int* solution) : solution(solution), EMPTY_VALUE(b.EMPTY_VALUE)
{
    std::memcpy(rowOccupants, b.rowOccupants, sizeof(uint16_t) * WIDTH);
    std::memcpy(colOccupants, b.colOccupants, sizeof(uint16_t) * WIDTH);
    std::memcpy(boxOccupants, b.boxOccupants, sizeof(uint16_t) * WIDTH);
    std::memcpy(solution, b.solution, sizeof(int) * CELL_COUNT);
    EmptyCells = b.EmptyCells;
}




template<int BASE>
void Sudoku::Board<BASE>::SetValue(Cell cell, uint16_t value)
{
    solution[cell.RowInd * WIDTH + cell.ColInd] = __builtin_ffs(value);
    Eliminate(cell, value);
}


template<int BASE>
void Sudoku::Board<BASE>::SetValue(Cell cell, int value)
{
    solution[cell.RowInd * WIDTH + cell.ColInd] = value;
    Eliminate(cell, (uint16_t) 1 << value - 1);
}

template<int BASE>
int* Sudoku::Board<BASE>::GetSolution() const
{
    return solution;
}

template<int BASE>
void Sudoku::Board<BASE>::Eliminate(Cell& cell, uint16_t value)
{
    rowOccupants[cell.RowInd] ^= value;
    colOccupants[cell.ColInd] ^= value;
    boxOccupants[cell.BoxInd] ^= value;
}


template class Sudoku::Board<2>;
template class Sudoku::Board<3>;
template class Sudoku::Board<4>;