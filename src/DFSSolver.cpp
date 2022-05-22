#include <stack>
#include "Board.h"
#include "stdint.h"
namespace Sudoku
{
    template<int BASE>
    class DFSSolver
    {


        public:
            static bool Solve(const int* puzzle, int* solution)
            {
                std::stack<Board<BASE>*> stack; 
                stack.push(new Board<BASE>(puzzle));
                while(stack.size() != 0)
                {
                    Board<BASE> *board = stack.top();
                    stack.pop();
                    
                    if (board->EmptyCellsCount == 0) 
                    {
                        memcpy(solution, board->GetSolution(), sizeof(int) * board->CELL_COUNT);
                        return true;
                    }
                    

                    Cell cell = board->EmptyCells[board->EmptyCellsCount - 1];
                    uint16_t occupants = board->GetOccupants(cell);
                    uint16_t nextCandidate = 0;
                    
                    while(occupants != board->CELL_COMPLETELY_OCCUPIED)
                    {
                        nextCandidate = Board<BASE>::NextCandidate(occupants);
                        Board<BASE>* newBoard = new Board<BASE>(*board);
                        newBoard->SetValue(cell, nextCandidate);
                        newBoard->EmptyCellsCount--;
                        stack.push(newBoard);
                        occupants ^= nextCandidate;
                    }
                    delete board; 
                }
                return false;
            }
   


    };

    template class DFSSolver<3>;
    template class DFSSolver<4>;
}
