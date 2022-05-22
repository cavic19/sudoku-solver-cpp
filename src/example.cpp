#include <iostream>
#include "C:\Program Files (x86)\Microsoft SDKs\MPI\Include\mpi.h"
#include "Parser.h"
#include "Logging.h"
#include "BacktrackingSolver.h"
#include <string>
#include <queue>
#include <tuple>

const int BASE = 3;
const int WIDTH = BASE * BASE;
const int CELL_COUNT = WIDTH * WIDTH;

int puzzle[CELL_COUNT];
int actualSolution[CELL_COUNT];

void InitPuzzles(std::string puzzleLine, bool withSolution);
void generateBoards(Sudoku::Board<BASE> &bIn, const int n, Sudoku::Board<BASE>** bOut);
int main(int argc, char** argv)
{
    int nproc, iproc;
    InitPuzzles(
        "8..........36......7..9.2...5...7.......457.....1...3...1....68..85...1..9....4..;812753649943682175675491283154237896369845721287169534521974368438526917796318452", 
        true);
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &iproc);

    Sudoku::Board<BASE> boardOrig(puzzle);
    Sudoku::Board<BASE>* boardPool[8];
    generateBoards(boardOrig, 8, boardPool);
    for (int i = 0; i < 8; i++)
    {
        std::cout << i << std::endl;
        Sudoku::printBoardWithCandidates(boardPool[i]);
        std::cout << std::endl << std::endl;
    }
    






    // Sudoku::BacktrackingSolver<BASE> solver(*boardPool[iproc]);
    // if(solver.Solve())
    // {
    //     std::cout << "Process " << iproc << " found a solution!" << std::endl;
    //     Sudoku::assertPuzzles(*boardPool[iproc], actualSolution);
    // }
    // else
    // {
    //     std::cout << "Process " << iproc << " failed." << std::endl;
    // }

    //     delete boardPool[iproc];
    
    MPI_Finalize();
    return 0;
}


void InitPuzzles(std::string puzzleLine, bool withSolution = false)
{
    Sudoku::Parser p(WIDTH);
    if (withSolution)
    {

        p.Parse(puzzleLine, puzzle, actualSolution);
    }
    else
    {
        p.Parse(puzzleLine, puzzle);
    }
}



void generateBoards(Sudoku::Board<BASE> &bIn, const int n, Sudoku::Board<BASE>** bOut)
{
    int index = 0;
    std::queue<Sudoku::Board<BASE>*> queue;
    queue.push(&bIn);

    while(index < n)
    {
        Sudoku::Board<BASE>* b = queue.front();
        queue.pop();
        Sudoku::Cell cell = b->EmptyCells[b->EmptyCellsCount - 1];
        uint16_t occupants = b->GetOccupants(cell);
        uint16_t candidate = Sudoku::Board<BASE>::NextCandidate(occupants);
        occupants ^= candidate;

        while(occupants <= b->CELL_COMPLETELY_OCCUPIED)
        {
            Sudoku::Board<BASE>* nextBoard = new Sudoku::Board<BASE>(*b);
            queue.push(nextBoard);
            bOut[index++] = nextBoard;

            if(index == n)
            {
                nextBoard->SetExtraOccupant(cell, occupants ^ candidate);
                break;
            }
            nextBoard->SetValue(cell, candidate);
            nextBoard->EmptyCellsCount--;
            candidate = Sudoku::Board<BASE>::NextCandidate(occupants);
            occupants ^= candidate;
        }
    }
}