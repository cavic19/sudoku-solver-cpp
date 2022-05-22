#include <iostream>
#include "C:\Program Files (x86)\Microsoft SDKs\MPI\Include\mpi.h"
#include "Parser.h"
#include "Logging.h"
#include "BacktrackingSolver.h"
#include "BaordGenerator.h"
#include <string>
#include <queue>
#include <chrono>

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
        "9..8...........5............2..1...3.1.....6....4...7.7.86.........3.1..4.....2..", 
        false);
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &iproc);
    auto start = std::chrono::steady_clock::now();
    
    Sudoku::Board<BASE> boardOrig(puzzle);
    std::queue<Sudoku::Board<BASE>*> queue;
    queue.push(&boardOrig);
    Sudoku::BoardGenerator::Generate(queue, nproc);

    for (int i = 0; i < iproc; i++) queue.pop();
    Sudoku::BacktrackingSolver<BASE> solver(*queue.front());
    if(solver.Solve())
    {
        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
        std::cout << "Process " << iproc << " found a solution in " << elapsed << "ms" << std::endl;
        // Sudoku::assertPuzzles(*queue.front(), actualSolution);
        Sudoku::printPuzzle(queue.front());
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
