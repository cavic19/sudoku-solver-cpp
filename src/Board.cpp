#include "Board.h"
#include <cstring>

bool Sudoku::operator==(const Sudoku::Cell& cell1, const Sudoku::Cell& cell2)
{
    return cell1.RowInd == cell2.RowInd && cell1.ColInd == cell2.ColInd;
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
                EmptyCells[EmptyCellsCount++] = {row, col, box};
            }
        }
}

template<int BASE>
Sudoku::Board<BASE>::Board(const int* puzzle, const int emptyValue) : EMPTY_VALUE(emptyValue)
{
    std::memcpy(solution, puzzle, sizeof(int) * CELL_COUNT);
    Init();
}

template<int BASE>
Sudoku::Board<BASE>::Board(const Board<BASE> &b) : EMPTY_VALUE(b.EMPTY_VALUE)
{
    for (int i = 0; i < WIDTH; i++)
    {
        rowOccupants[i] = b.rowOccupants[i];
        colOccupants[i] = b.colOccupants[i];
        boxOccupants[i] = b.boxOccupants[i];
        extraOccupants[i] = b.extraOccupants[i];

        EmptyCells[i] = b.EmptyCells[i];
        solution[i] = b.solution[i];
    }
    EmptyCellsCount =  b.EmptyCellsCount;
    for (int i = WIDTH; i < EmptyCellsCount; i++)
    {
        EmptyCells[i] = b.EmptyCells[i];
        solution[i] = b.solution[i];
    }

    for (int i = EmptyCellsCount; i < CELL_COUNT; i++)
    {
        solution[i] = b.solution[i];
    }
}

template<int BASE>
void Sudoku::Board<BASE>::SetValueWithoutElimination(Cell cell, uint16_t value)
{
    solution[cell.RowInd * WIDTH + cell.ColInd] = __builtin_ffs(value);
}

template<int BASE>
void Sudoku::Board<BASE>::SetValue(Cell cell, uint16_t value)
{
    SetValueWithoutElimination(cell, value);
    Eliminate(cell, value);
}


template<int BASE>
void Sudoku::Board<BASE>::SetValue(Cell cell, int value)
{
    solution[cell.RowInd * WIDTH + cell.ColInd] = value;
    Eliminate(cell, (uint16_t) 1 << value - 1);
}

template<int BASE>
const int* Sudoku::Board<BASE>::GetSolution() const
{
    return solution;
}




template class Sudoku::Board<2>;
template class Sudoku::Board<3>;
template class Sudoku::Board<4>;