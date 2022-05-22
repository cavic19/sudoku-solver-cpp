#include <iostream>
#include "C:\Program Files (x86)\Microsoft SDKs\MPI\Include\mpi.h"
#include "Parser.h"
#include "Logging.h"
#include "BacktrackingSolver.h"
#include "BaordGenerator.h"
#include <string>
#include <queue>


const int BASE = 3;
const int WIDTH = BASE * BASE;
const int CELL_COUNT = WIDTH * WIDTH;

int puzzle[CELL_COUNT];
int actualSolution[CELL_COUNT];

void InitPuzzles(std::string puzzleLine, bool withSolution);
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

    std::queue<Sudoku::Board<BASE>*> queue;
    queue.push(&boardOrig);
    Sudoku::BoardGenerator::Generate(queue, nproc);

    for (int i = 0; i < iproc; i++) queue.pop();

    Sudoku::BacktrackingSolver<BASE> solver(*queue.front());
    if(solver.Solve())
    {
        std::cout << "Process " << iproc << " found a solution!" << std::endl;
        Sudoku::assertPuzzles(*queue.front(), actualSolution);
    }
    else
    {
        std::cout << "Process " << iproc << " failed." << std::endl;
    }
  
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
