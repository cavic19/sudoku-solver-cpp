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
void Sudoku::printBoard(const Board<BASE>* board)
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


bool Sudoku::assertPuzzles(const int* puzzle1, const int* puzzle2)
{
    std::string errorMessage;
    bool isSuccess = true;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (puzzle1[i * 16 + j] == puzzle2[i * 16 + j])
            {
                errorMessage  += std::to_string(puzzle1[i * 16 + j]) + ", ";
            }
            else
            {   
                errorMessage  += std::to_string(puzzle1[i * 16 + j]) + "[" + std::to_string(puzzle2[i * 16 + j]) + "], ";
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

template void Sudoku::printBoard<2>(const Board<2>*);
template void Sudoku::printBoard<3>(const Board<3>*);
template void Sudoku::printBoard<4>(const Board<4>*);