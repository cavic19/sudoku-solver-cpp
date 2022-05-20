#include "Logging.h"
#include <iostream>
#include <string>

template<int BASE>
void Sudoku::printBoardWithCandidates(const Board<BASE>* board)
{
    for (int row = 0; row < board->WIDTH; row++)
    {
        for (int col = 0; col < board->WIDTH; col++)
        {
            if(board->GetSolution()[row * 9 + col] != -1)
            {
                std::cout << board->GetSolution()[row * 9 + col] << ",";
                continue;
            }
            int box = (row / BASE) * BASE + col / BASE;
            Sudoku::Cell c = {row, col, box};
            auto occupants = board->GetOccupants(c);
            short candiates = board->CELL_COMPLETELY_OCCUPIED ^ occupants;
            for (int i = 0; i < board->WIDTH; i++)
            {
                if(candiates & (1 << i))
                {
                    std::cout << i + 1;
                }
            }
            std::cout << ",";
            
        }
        std::cout << std::endl;
    }
}

template<int BASE>
void Sudoku::printPuzzle(const Board<BASE>* board)
{
    printPuzzle(board->GetSolution(), board->WIDTH);
}


void Sudoku::printPuzzle(const int* puzzle, int width)
{
    for (int row = 0; row < width; row++)
    {
        for (int col = 0; col < width; col++)
        {
            std::cout << puzzle[row * width + col] << ",";
        }
        std::cout << std::endl;
    }
    
}


template<int BASE>
bool Sudoku::assertPuzzles(const Board<BASE> &board, const int* expectedSolution)
{
    return assertPuzzles(board.GetSolution(), expectedSolution, board.WIDTH);
}


bool Sudoku::assertPuzzles(const int* puzzle1, const int* puzzle2, int width)
{
    std::string errorMessage;
    bool isSuccess = true;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (puzzle1[i * width + j] == puzzle2[i * width + j])
            {
                errorMessage  += std::to_string(puzzle1[i * width + j]) + ", ";
            }
            else
            {   
                errorMessage  += std::to_string(puzzle1[i * width + j]) + "[" + std::to_string(puzzle2[i * width + j]) + "], ";
                isSuccess = false;
            }
        }
        errorMessage += '\n';
    }
    if (!isSuccess)
    {
        std::cout << "Assertion failed:" << std::endl; 
        std::cout << errorMessage << std::endl;
    }
    else
    {
        std::cout << "Assertion succeeded!" << std::endl; 
    }   
    return isSuccess;
}


template void Sudoku::printBoardWithCandidates<2>(const Board<2>*);
template void Sudoku::printBoardWithCandidates<3>(const Board<3>*);
template void Sudoku::printBoardWithCandidates<4>(const Board<4>*);

template void Sudoku::printPuzzle<2>(const Board<2>*);
template void Sudoku::printPuzzle<3>(const Board<3>*);
template void Sudoku::printPuzzle<4>(const Board<4>*);

template bool Sudoku::assertPuzzles<2>(const Board<2> &board, const int* expectedSolution);
template bool Sudoku::assertPuzzles<3>(const Board<3> &board, const int* expectedSolution);
template bool Sudoku::assertPuzzles<4>(const Board<4> &board, const int* expectedSolution);