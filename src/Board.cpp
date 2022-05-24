#include "Board.h"
#include <cstring>


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


// template<int BASE>
// MPI_Datatype Sudoku::Board<BASE>::InitializeMPIBoardDataType()
// {   

//     MPI_Datatype temp;
//     const int nitems = 7;
//     int types[nitems] = 
//         {
//         MPI_INT,            //solution[CELL_COUNT]
//         MPI_INT16_T,        //rowOccupants[WIDTH]
//         MPI_INT16_T,        //colOccupants[WIDTH]
//         MPI_INT16_T,        //boxOccupants[WIDTH]
//         MPI_INT16_T,        //extraOccupants[WIDTH]
//         MPI_CELL,    //emptyCells[CELL_COUNT]  
//         MPI_INT             //emptyCellsCount
//         };   

//     int blockLengths[nitems] = 
//         {
//             CELL_COUNT,
//             WIDTH,
//             WIDTH,
//             WIDTH,
//             WIDTH,
//             CELL_COUNT,
//             1
//         };

//     MPI_Aint offsets[nitems]; 
//     offsets[0] = offsetof(Board<BASE>, solution);
//     offsets[1] = offsetof(Board<BASE>, rowOccupants);
//     offsets[2] = offsetof(Board<BASE>, colOccupants);
//     offsets[3] = offsetof(Board<BASE>, boxOccupants);
//     offsets[4] = offsetof(Board<BASE>, extraOccupants);
//     offsets[5] = offsetof(Board<BASE>, EmptyCells);
//     offsets[6] = offsetof(Board<BASE>, EmptyCellsCount);

//     MPI_Type_create_struct(nitems, blockLengths, offsets, types, &temp);
//     MPI_Type_commit(&temp);
//     return temp;
// }

// template<int BASE>
// MPI_Datatype Sudoku::Board<BASE>::InitializeMPICellDataType()
// {
//     MPI_Datatype temp;
//     const int nitems = 3;
//     int types[nitems] = {MPI_INT, MPI_INT, MPI_INT};
//     int blockLengths[nitems] = {1, 1, 1};
//     MPI_Aint offsets[nitems];
//     offsets[0] = offsetof(Cell, RowInd);
//     offsets[1] = offsetof(Cell, ColInd);
//     offsets[2] = offsetof(Cell, BoxInd);
//     MPI_Type_create_struct(nitems, blockLengths, offsets, types, &temp);
//     MPI_Type_commit(&temp);
//     return temp;
// }





template class Sudoku::Board<2>;
template class Sudoku::Board<3>;
template class Sudoku::Board<4>;

// template<int BASE>
// MPI_Datatype Sudoku::Board<BASE>::MPI_CELL = InitializeMPICellDataType();
// template<int BASE>
// MPI_Datatype Sudoku::Board<BASE>::MPI_BOARD = InitializeMPIBoardDataType();